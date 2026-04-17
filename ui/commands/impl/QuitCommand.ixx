//
// Created by max on 4/16/26.
//

module;

#include <string>
#include <map>
#include <print>

export module Command.Quit;

import Command;
import UI.IGameServer;

export class QuitCommand : public Command {
    IGameServer* gameServer = nullptr;
public:
    explicit QuitCommand(IGameServer* gameServer) : Command() {
        this->gameServer = gameServer;
    }

    [[nodiscard]] std::string getName() const override {
        return "quit";
    }
    void exec(const int clientId, std::map<std::string, std::string> args) const override {
        if (!gameServer->getClient(clientId).host) {
            std::println("Unauthorized!");
            return;
        }
        std::println("Quitting!");
    }
};
