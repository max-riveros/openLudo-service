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
    std::unordered_map<uint8_t, Pawn, PawnHash> pawns;
public:
    virtual ~Board() = default;

    virtual uint8_t getSize() = 0;
    virtual const Field* getFields() = 0;
    virtual const std::unordered_map<uint8_t, Pawn, PawnHash>& getPawns() {
        return pawns;
    }
    virtual Field& getField(uint8_t position) = 0;
    virtual Pawn &getPawn(const uint8_t id) {
        if (!pawns.contains(id)) throw std::out_of_range("Tried to access a Pawn that's not on the board!");
        return pawns[id];
    }
    virtual void addPawns(Pawn* pawns, const size_t count) {
        for (size_t i = 0; i < count; i++) {
            this->pawns.emplace(pawns[i].getId(), pawns[i]);
        }
    }
    virtual void removePawns(Pawn* pawns, const size_t count) {
        for (size_t i = 0; i < count; i++) {
            this->pawns.erase(pawns[i].getId());
        }
    }
    virtual void move(Pawn& pawn, const uint8_t targetPosition) {
        Field& field = getField(pawn.getPosition());
        field.getPawns().erase(pawn.getId());
        field = getField(targetPosition);
        pawn.setPosition(targetPosition);
        field.getPawns().emplace(pawn.getId(), pawn);
    }
    virtual void kill(Pawn& pawn) {
        Field& field = getField(pawn.getPosition());
        field.getPawns().erase(pawn.getId());
        pawn.setPosition(pawn.getStartPosition());
        pawn.setDead(true);
    }
    virtual void revive(Pawn& pawn) {
        Field& field = getField(pawn.getPosition());
        field.getPawns().emplace(pawn.getId(), pawn);
        pawn.setDead(false);
    }
};
