//
// Created by max on 4/16/26.
//

module;

#include <cstring>
#include <string>
#include <map>
#include <print>

export module Command.Register;

import Command;
import UI.IGameServer;
import Player.Default;
import Pawn.Default;

export class RegisterCommand : public Command {
    IGameServer* gameServer = nullptr;
public:
    explicit RegisterCommand(IGameServer* gameServer) : Command() {
        this->gameServer = gameServer;
    }

    [[nodiscard]] std::string getName() const override {
        return "register";
    }
    void exec(const int clientId, std::map<std::string, std::string> args) const override {
        Client& client = gameServer->getClient(clientId);
        if (client.token != nullptr) return;

        char* token = new char[6];
        std::strcpy(token, "00000");
        client.token = token;

        std::println("registered client ({})!", client.token);
    }
};
