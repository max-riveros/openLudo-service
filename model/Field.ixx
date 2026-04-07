//
// Created by max on 07.04.26.
//

module;

#include <cstdint>
#include <vector>

export module Field;

import Pawn;

export class Field {
protected:
    bool safe = false;
    uint8_t position = 0;
    std::vector<Pawn> pawns;
public:
    virtual ~Field() = default;

    virtual bool isSafe() {
        return safe;
    }
    virtual uint8_t getPosition() {
        return position;
    }
    virtual const std::vector<Pawn>& getPawns() {
        return pawns;
    }
};
