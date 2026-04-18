//
// Created by max on 4/16/26.
//

module;

#include <map>
#include <print>
#include <sstream>
#include <thread>
#include <arpa/inet.h>
#include <sys/socket.h>

#define TOKEN_SIZE 5;

module UI.GameServer;

import Command.Quit;
import Command.Register;
import Command.RollDice;
import Command.SelectPawn;
import Command.StartGame;

std::string getAddressString(const sockaddr_in addr) {
    char ip[INET_ADDRSTRLEN];

    inet_ntop(AF_INET, &addr.sin_addr, ip, sizeof(ip));

    const int port = ntohs(addr.sin_port);

    std::ostringstream oss;
    oss << ip << ":" << port;

    return oss.str();
}

void bindTo(const int serverSocket, const in_addr_t ip, const in_port_t port) {
    sockaddr_in bindingAddress{};
    bindingAddress.sin_family = AF_INET;
    bindingAddress.sin_port = htons(port);
    bindingAddress.sin_addr.s_addr = ip;
    bind(serverSocket, reinterpret_cast<sockaddr *>(&bindingAddress), sizeof(bindingAddress));
    std::println("Binding to address {} at socket {}!", getAddressString(bindingAddress), serverSocket);
}


std::map<std::string, std::string> parse(const std::string& input) {
    std::map<std::string, std::string> result;

    std::stringstream ss(input);
    std::string pair;

    while (std::getline(ss, pair, ';')) {
        auto pos = pair.find('=');
        if (pos != std::string::npos) {
            result[pair.substr(0, pos)] = pair.substr(pos + 1);
        }
    }

    return result;
}

void GameServer::broadcast(const std::string message) {
    for (Client& client : clients) {
        client.sendMessage(message);
    }
}

void GameServer::handleMessage(const Client& client, const char buffer[INPUT_BUFFER_SIZE]) const {
    std::println("Got \"{}\"", buffer);
    std::map data = parse(buffer);
    if (!data.contains("cmd")) {
        return;
    }
    const std::string cmd = data["cmd"];

    if (cmd == "register") {
        commands.at(cmd)->exec(client.clientId, data);
        return;
    }

    if (client.token == nullptr) {
        std::println("Client is not registered!");
        return;
    }
    if (!data.contains("token") || data["token"] != client.token) {
        std::println("Invalid token! ({} vs {})", data["token"], client.token);
        return;
    }

    if (!commands.contains(cmd)) {
        std::println("Unknown command! ({})", cmd);
        return;
    }
    commands.at(cmd)->exec(client.clientId, data);

    std::println("Command done.");
}

void GameServer::listenClient(Client& client) const {
    if (client.socket == -1) return;

    std::string clientString = std::to_string(client.clientId) + " addr " + getAddressString(client.address);
    std::println("Listening to client {}...", clientString);
    while (listening) {
        char buffer[1024] = {};
        int bytes = recv(client.socket, buffer, sizeof(buffer), 0);
        if (bytes == 0) {
            std::println("Client {} disconnected!", clientString);
            close(client.socket);
            client.socket = -1;
            return;
        }
        if (bytes < 0) {
            std::println("There was an error while receiving client data!");
            close(client.socket);
            client.socket = -1;
            return;
        }
        std::println("Received {} bytes from {}!", bytes, clientString);

        handleMessage(client, buffer);
    }
    std::println("Stopped listening to client {}...", getAddressString(client.address));
}

void GameServer::connectClient(int& id) {
    Client& client = getClient(id);
    if (client.socket >= 0) return;

    sockaddr_in clientAddress{};
    socklen_t clientAddressLength = sizeof(clientAddress);
    const int socket = accept(serverSocket, reinterpret_cast<sockaddr *>(&clientAddress), &clientAddressLength);
    if (socket < 0) {
        std::perror("Accept failed");
        return;
    }

    for (Client& otherClient : clients) {
        if (otherClient.address.sin_addr.s_addr == clientAddress.sin_addr.s_addr && otherClient.address.sin_port == clientAddress.sin_port) {
            std::println("Reconnected client!");
            otherClient.socket = socket;
            id = 0;
            return;
        }
    }

    client.socket = socket;
    client.address = clientAddress;
    if (playerCount == 0) {
        client.host = true;
        client.color = RED;
    } else if (playerCount == 1) {
        client.color = BLUE;
    } else if (playerCount == 2) {
        client.color = YELLOW;
    } else {
        client.color = GREEN;
    }
    client.clientId = id;
    std::println("Client {} addr {} connected at socket {}!", id, getAddressString(clientAddress), client.socket);
    playerCount++;

    broadcast("event=clientConnect;id="+std::to_string(id));

    client.thread = std::thread(&GameServer::listenClient, this, std::ref(client));
}

void GameServer::connectClients() {
    std::println("Waiting for connection attempts...");
    for (int i = 0; i < MAX_CLIENTS; i++) {
        connectClient(i);
    }
    for (int i = 0; i < MAX_CLIENTS; i++) {
        Client& client = getClient(i);
        if (client.thread.joinable()) {
            client.thread.join();
        }
    }
}

void GameServer::addCommand(Command* command) {
    commands[command->getName()] = command;
}

void GameServer::addCommands() {
    Command* command = new QuitCommand(this);
    addCommand(command);
    command = new RegisterCommand(this);
    addCommand(command);
    command = new RollDiceCommand(this);
    addCommand(command);
    command = new SelectPawnCommand(this);
    addCommand(command);
    command = new StartGameCommand(this);
    addCommand(command);
}

void GameServer::onGameStart() {
    for (const Player& player : getGame()->getPlayers()) {
        std::string message;
        message.reserve(256);
        message = "event=playerSetup";
        message += ";id="+player.getId();
        message += ";color="+std::to_string(player.getColor());
        message += ";startPosition="+std::to_string(player.getPawns().back().getStartPosition());
        message += ";endPosition="+std::to_string(player.getPawns().back().getEndPosition());
        message += ";pawns=";
        for (const Pawn& pawn : player.getPawns()) {
            message += std::to_string(pawn.getId()) + ",";
        }
        broadcast(message);
    }
    const std::string message = "event=gameStart;playerCount="+std::to_string(playerCount);
    broadcast(message);
}
void GameServer::onPlayerTurn(const Player& player) {
    broadcast("event=playerTurn;player=" + player.getId());
}
void GameServer::onWaitingForDice() {
    broadcast("event=waitingForDice");
}
void GameServer::onDiceRolled(const uint8_t value) {
    broadcast("event=diceRolled;value=" + std::to_string(value));
}
void GameServer::onWaitingForSelect() {
    broadcast("event=waitingForSelect");
}
void GameServer::onSelected(const Pawn& pawn) {
    broadcast("event=selected;pawn=" + std::to_string(pawn.getId()));
}
void GameServer::onPlayerSkipped() {
    broadcast("event=playerSkipped");
}

void GameServer::onPawnKilled(const Pawn& killer, const Pawn& killed) {
    broadcast("event=pawnKilled;killer=" + std::to_string(killer.getId()) + ";killed" + std::to_string(killed.getId()));
}
void GameServer::onPawnRevived(const Pawn& pawn) {
    broadcast("event=pawnRevived;pawn=" + std::to_string(pawn.getId()));
}
void GameServer::onPawnSaved(const Pawn& pawn) {
    broadcast("event=pawnSaved;pawn=" + std::to_string(pawn.getId()));
}
void GameServer::onPawnMovedToGoalArea(const Pawn& pawn) {
    broadcast("event=pawnMovedToGoalArea;pawn=" + std::to_string(pawn.getId()));
}
void GameServer::onPawnMoved(const Pawn& pawn, const Field& from, const Field& to) {
    broadcast("event=pawnMoved;pawn=" + std::to_string(pawn.getId()) + ";from=" + std::to_string(from.getPosition()) + ";to=" + std::to_string(to.getPosition()));
}
void GameServer::onGameOver(const Player& player) {
    broadcast("event=gameOver;player=" + player.getId());
}
