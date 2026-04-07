//
// Created by max on 07.04.26.
//

module;
#include <cstdint>

export module Pawn;

// TODO: Add color
export class Pawn {
protected:
    uint8_t id = 0;
    bool dead = true;
    bool saved = false;
    bool inGoalArea = false;

public:
    virtual ~Pawn() = default;

    virtual uint8_t getId() = 0;
    virtual bool isDead() = 0;
    virtual bool isSaved() = 0;
    virtual bool isInGoalArea() = 0;
    virtual void setDead(bool value) = 0;
    virtual void setSaved(bool value) = 0;
    virtual void setInGoalArea(bool value) = 0;
};