//
// Created by max on 4/16/26.
//

module;

#include <string>
#include <map>
#include <print>

export module Command.SelectPawn;

import Command;
import UI.IGameServer;

bool isPositiveInt(const std::string& s) {
    if (s.empty()) return false;

    for (const char c : s) {
        if (!std::isdigit(static_cast<unsigned char>(c))) {
            return false;
        }
    }

    return true;
}

export class SelectPawnCommand : public Command {
    IGameServer* gameServer = nullptr;
public:
    explicit SelectPawnCommand(IGameServer* gameServer) : Command() {
        this->gameServer = gameServer;
    }

    [[nodiscard]] std::string getName() const override {
        return "selectPawn";
    }
    void exec(const int clientId, std::map<std::string, std::string> args) const override {
        if (!gameServer->getGame()) return;
        Client& client = gameServer->getClient(clientId);
        if (!args.contains("pawn") || !isPositiveInt(args["pawn"])) {
            client.sendMessage("cmd=selectPawn;response=1"); // Invalid pawn
            return;
        }
        if (std::to_string(client.playerId) != gameServer->getGame()->getTurn().getId()) {
            client.sendMessage("cmd=selectPawn;response=2"); // Not clients turn
            return;
        }
        const int pawnId = std::stoi(args["pawn"]);
        bool exists = false;
        for (const auto& pawn : gameServer->getGame()->getPossiblePawns()) {
            if (pawn.getId() == pawnId) {
                exists = true;
                break;
            }
        }
        if (!exists) {
            client.sendMessage("cmd=selectPawn;response=1"); // Invalid pawn
            return;
        }
        gameServer->getGame()->selectPawn(pawnId);
    }
};
