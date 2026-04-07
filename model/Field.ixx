//
// Created by max on 07.04.26.
//

module;

#include <cstdint>
#include <unordered_map>

export module Field;

import Pawn;

export class Field {
protected:
    bool safe = false;
    uint8_t position = 0;
    std::unordered_map<uint8_t, Pawn, PawnHash> pawns;
public:
    virtual ~Field() = default;

    virtual bool isSafe() {
        return safe;
    }
    virtual uint8_t getPosition() {
        return position;
    }
    virtual std::unordered_map<uint8_t, Pawn, PawnHash>& getPawns() {
        return pawns;
    }
};
