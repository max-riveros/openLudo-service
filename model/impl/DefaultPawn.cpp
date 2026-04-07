//
// Created by max on 07.04.26.
//

module;
#include <cstdint>

export module DefaultPawn;

export import Pawn;

export class DefaultPawn : public Pawn {
public:
    explicit DefaultPawn(const uint8_t id) {
        this->id = id;
    }
};