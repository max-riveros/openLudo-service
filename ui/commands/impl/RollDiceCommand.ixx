//
// Created by max on 4/16/26.
//

module;

#include <string>
#include <map>
#include <print>

export module Command.RollDice;

import Command;
import UI.IGameServer;

export class RollDiceCommand : public Command {
    IGameServer* gameServer = nullptr;
public:
    explicit RollDiceCommand(IGameServer* gameServer) : Command() {
        this->gameServer = gameServer;
    }

    [[nodiscard]] std::string getName() const override {
        return "rollDice";
    }
    void exec(const int clientId, std::map<std::string, std::string> args) const override {
        if (!gameServer->getGame()) return;
        Client& client = gameServer->getClient(clientId);
        if (std::to_string(client.playerId) != gameServer->getGame()->getTurn().getId()) {
            client.sendMessage("cmd=rollDice;response=2"); // Not clients turn
            return;
        }
        gameServer->getGame()->rollDice();
    }
};
