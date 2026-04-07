//
// Created by max on 07.04.26.
//

module;
#include <vector>
#include <string>

export module Player;

export import Pawn;

export class Player {
protected:
    std::string id;
    std::vector<Pawn> pawns;
public:
    virtual ~Player() = default;

    virtual const std::vector<Pawn>& getPawns() {
        return pawns;
    }
    virtual const std::string& getId() {
        return id;
    }
    virtual const Color& getColor() {
        return pawns.front().getColor();
    }
};
