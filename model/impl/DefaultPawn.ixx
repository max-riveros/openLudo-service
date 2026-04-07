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

    uint8_t getId() override {
        return id;
    }
    bool isDead() override {
        return dead;
    }
    bool isSaved() override {
        return saved;
    }
    bool isInGoalArea() override {
        return inGoalArea;
    }
    void setInGoalArea(const bool value) override {
        inGoalArea = value;
    }
    void setDead(const bool value) override {
        dead = value;
    }
    void setSaved(const bool value) override {
        saved = value;
    }
};