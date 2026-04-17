//
// Created by max on 4/16/26.
//

module;

#include <string>
#include <map>
#include <print>

export module Command.StartGame;

import Command;
import UI.IGameServer;

export class StartGameCommand : public Command {
    IGameServer* gameServer = nullptr;
public:
    explicit StartGameCommand(IGameServer* gameServer) : Command() {
        this->gameServer = gameServer;
    }

    [[nodiscard]] std::string getName() const override {
        return "start";
    }
    void exec(const int clientId, std::map<std::string, std::string> args) const override {
        if (!gameServer->getClient(clientId).host) {
            std::println("Unauthorized!");
            return;
        }
        gameServer->initGame();
        gameServer->getGame()->start();
    }
};
