//
// Created by max on 07.04.26.
//

module;
#include <cstdint>

export module Pawn.Default;

export import Pawn;

export class DefaultPawn : public Pawn {
public:
    explicit DefaultPawn(const uint8_t id, const Color& color, const uint8_t startPosition, const uint8_t endPosition) {
        this->id = id;
        this->color = color;
        this->startPosition = startPosition;
        this->endPosition = endPosition;
        this->position = startPosition;
    }
};
