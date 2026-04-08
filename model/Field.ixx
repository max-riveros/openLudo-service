//
// Created by max on 07.04.26.
//

module;

#include <cstdint>
#include <memory>
#include <stdexcept>
#include <vector>

export module Field;

import Pawn;

export class Field {
protected:
    std::vector<Pawn*> pawns;
    uint8_t position = 0;
    bool safe = false;
public:
    virtual ~Field() = default;

    Field() = default;

    Field(const Field&) = delete;
    Field& operator=(const Field&) = delete;

    Field(Field&&) = default;
    Field& operator=(Field&&) = default;

    virtual bool isSafe() {
        return safe;
    }
    virtual uint8_t getPosition() {
        return position;
    }
    virtual const std::vector<Pawn*>& getPawns() {
        return pawns;
    }
    virtual Pawn& getPawn(const uint8_t id) {
        for (const auto& pawn : pawns) {
            if (pawn->getId() == id) return *pawn;
        }
        throw std::logic_error("Pawn not found");
    }
    virtual void addPawn(Pawn& pawn) {
        pawns.emplace_back(&pawn);
    }
    virtual void removePawn(const Pawn& pawn) {
        for (auto it = pawns.begin(); it != pawns.end(); ++it) {
            Pawn* other = *it;
            if (other->getId() == pawn.getId()) {
                pawns.erase(it);
                return;
            }
        }
    }
};
