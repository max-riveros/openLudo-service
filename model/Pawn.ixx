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

    virtual uint8_t getId() {
        return id;
    };
    virtual bool isDead() {
        return dead;
    };
    virtual bool isSaved() {
        return saved;
    };
    virtual bool isInGoalArea() {
        return inGoalArea;
    };
    virtual void setDead(bool const value) {
        dead = value;
    };
    virtual void setSaved(bool const value) {
        saved = value;
    };
    virtual void setInGoalArea(bool const value) {
        inGoalArea = value;
    };
};