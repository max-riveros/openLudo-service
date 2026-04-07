//
// Created by max on 07.04.26.
//

module;

#include <cstdint>
#include <stdexcept>
#include <unordered_map>

export module Board;

export import Field;
export import Pawn;

export class Board {
protected:
    std::unordered_map<uint8_t, Pawn> pawns;
public:
    virtual ~Board() = default;

    virtual uint8_t getSize() = 0;
    virtual const Field* getFields() = 0;
    virtual const std::unordered_map<uint8_t, Pawn>& getPawns() {
        return pawns;
    }
    virtual const Field& getField(uint8_t position) = 0;
    virtual const Pawn& getPawn(uint8_t const id) {
        if (!pawns.contains(id)) throw std::out_of_range("Tried to access a Pawn that's not on the board!");
        return pawns[id];
    }
};
