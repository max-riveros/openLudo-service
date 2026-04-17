//
// Created by max on 4/16/26.
//

module;

#include <print>
#include <unistd.h>
#include <map>
#include <sys/socket.h>
#include <netinet/in.h>
#include <thread>

#define TOKEN_SIZE 5;

export module UI.GameServer;

import UI.IGameServer;
import Game.Default;
import Game;
import Command;

export std::string getAddressString(sockaddr_in addr);

export void bindTo(int serverSocket, in_addr_t ip, in_port_t port);

export std::map<std::string, std::string> parse(const std::string& input);

export class GameServer : public IGameServer {
private:
    static constexpr int MAX_CLIENTS = 4;
    static constexpr int INPUT_BUFFER_SIZE = 1024;
    Client clients[MAX_CLIENTS] = {};
    std::map<std::string, Command*> commands;
    DefaultGame* game = nullptr;
    bool* listening = nullptr;
    int serverSocket = -1;
    int playerCount = 0;

protected:
    void handleMessage(const Client& client, const char buffer[INPUT_BUFFER_SIZE]) const override;
    void listenClient(Client& client) const override;
    void connectClient(int id) override;
    void addCommand(Command* command) override;
    void addCommands() override;
    void connectClients();
public:
    static constexpr in_port_t DEFAULT_PORT = 1221;

    explicit GameServer() : GameServer(INADDR_ANY, DEFAULT_PORT) {
        listening = new bool(false);
    }
    explicit GameServer(const in_addr_t ip, const in_port_t port) {
        serverSocket = socket(AF_INET, SOCK_STREAM, 0);
        bindTo(serverSocket, ip, port);
    }

    ~GameServer() override {
        GameServer::stop();
        delete(listening);
    }

    void broadcast(std::string message) override;

    Client& getClient(const int id) override {
        if (id >= MAX_CLIENTS) throw std::logic_error("Tried to access out of bounds client!");
        return clients[id];
    }

    Game* getGame() const override {
        return game;
    }
    void initGame() override {
        std::string playerIds[getPlayerCount()];
        uint8_t playerIndex = 1;
        for (Client& client : clients) {
            if (client.clientId <= 0) continue;
            client.playerId = client.clientId;
            playerIds[playerIndex] = std::to_string(client.clientId);
            playerIndex++;
        }
        game = new DefaultGame(playerIds, getPlayerCount(), this);
    }
    int getPlayerCount() const override {
        return playerCount;
    }

    void start() override {
        std::println("Starting server...");
        addCommands();

        listen(serverSocket, MAX_CLIENTS);
        *listening = true;

        connectClients();
    }

    void stop() const override {
        std::println("Stopping server...");
        *listening = false;
        close(serverSocket);
    }

    void onGameStart() override;
    void onPlayerTurn(const Player& player) override;
    void onWaitingForDice() override;
    void onDiceRolled(uint8_t value) override;
    void onWaitingForSelect() override;
    void onSelected(const Pawn& pawn) override;
    void onPlayerSkipped() override;

    void onPawnKilled(const Pawn& killer, const Pawn& killed) override;
    void onPawnRevived(const Pawn& pawn) override;
    void onPawnSaved(const Pawn& pawn) override;
    void onPawnMovedToGoalArea(const Pawn& pawn) override;
    void onPawnMoved(const Pawn& pawn, const Field& from, const Field& to) override;
    void onGameOver(const Player& player) override;
};
