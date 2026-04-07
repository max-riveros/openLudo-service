//
// Created by max on 07.04.26.
//

module;

#include <string>

export module Player.Default;
export import Player;

export class DefaultPlayer : public Player {
public:
    explicit DefaultPlayer(const std::string& id, const Pawn pawns[4]) {
        this->id = id;
        for (int i = 0; i < 4; i++) {
            this->pawns.push_back(pawns[i]);
        }
    }
};
