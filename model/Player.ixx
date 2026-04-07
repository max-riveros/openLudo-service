//
// Created by max on 07.04.26.
//

module;
#include <vector>
#include <string>

export module Player;

export import Pawn;

export class Player {
private:
    std::string name;
    std::vector<Pawn> pawns;
public:
    virtual ~Player() = default;

    virtual const std::vector<Pawn>& getPaws() {
        return pawns;
    }
    virtual const std::string& getName() {
        return name;
    }
    virtual const Color& getColor() {
        return pawns.front().getColor();
    }
};
