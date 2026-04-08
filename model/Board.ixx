//
// Created by max on 07.04.26.
//

module;

#include <cstdint>

export module Board;

export import Field;
export import Pawn;

export class Board {
public:
    virtual ~Board() = default;

    virtual uint8_t getSize() = 0;
    virtual const Field* getFields() = 0;
    virtual Field& getField(uint8_t position) = 0;
    virtual void move(Pawn& pawn, const uint8_t targetPosition) {
        Field& field = getField(pawn.getPosition());
        field.removePawn(pawn);
        Field& otherField = getField(targetPosition);
        pawn.setPosition(targetPosition);
        otherField.addPawn(pawn);
    }
    virtual void kill(Pawn& pawn) {
        Field& field = getField(pawn.getPosition());
        field.removePawn(pawn);
        pawn.setPosition(pawn.getStartPosition());
        pawn.setDead(true);
    }
    virtual void revive(Pawn& pawn) {
        Field& field = getField(pawn.getPosition());
        pawn.setDead(false);
        field.addPawn(pawn);
    }
};
