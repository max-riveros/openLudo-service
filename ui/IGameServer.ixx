//
// Created by max on 4/16/26.
//

module;

#include <netinet/in.h>
#include <thread>
#include <mutex>
#include <print>

#define TOKEN_SIZE 5;

export module UI.IGameServer;

import UI;
import Command;
import Game;
import Pawn;

export struct Client {
    std::mutex sendMutex;
    sockaddr_in address;
    std::thread thread;
    char* token = nullptr;
    int socket = -1;
    Color color;
    bool host = false;
    int8_t clientId = -1;

    ~Client() {
        delete[] token;
    }
    void sendMessage(const std::string& message) {
        if (socket == -1) return;

        std::lock_guard lock(sendMutex);

        size_t total = 0;
        std::string messageCopy = message;
        messageCopy+="\n";
        const size_t len = messageCopy.length();

        while (total < len) {
            const ssize_t sent = send(socket, messageCopy.c_str() + total, len - total, 0);
            if (sent <= 0) {
                close(socket);
                socket = -1;
                break;
            }
            total += sent;
        }
    }
};

export constexpr int INPUT_BUFFER_SIZE = 1024;

export class IGameServer : public UI {
protected:
    virtual void handleMessage(const Client& client, const char buffer[INPUT_BUFFER_SIZE]) const = 0;
    virtual void listenClient(Client& client) const = 0;
    virtual void connectClient(int& id) = 0;
    virtual void addCommand(Command* command) = 0;
    virtual void addCommands() = 0;
public:
    ~IGameServer() override = default;

    virtual void broadcast(std::string message) = 0;
    virtual Client& getClient(int id) = 0;
    [[nodiscard]] virtual Game* getGame() const = 0;
    [[nodiscard]] virtual int getPlayerCount() const = 0;
    virtual void initGame() = 0;
    void start() override = 0;
    virtual void stop() const = 0;
};
