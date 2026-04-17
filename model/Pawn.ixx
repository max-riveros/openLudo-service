//
// Created by max on 07.04.26.
//

module;
#include <cstdint>
#include <string>

export module Pawn;

export enum Color {
    RED,
    BLUE,
    GREEN,
    YELLOW,
};

export class Pawn {
protected:
    Color color = RED;
    bool dead = true;
    bool saved = false;
    bool inGoalArea = false;
    uint8_t id = 0;
    uint8_t position = 0;
    uint8_t startPosition = 0;
    uint8_t endPosition = 0;

public:
    virtual ~Pawn() = default;

    [[nodiscard]] virtual uint8_t getId() const {
        return id;
    }
    [[nodiscard]] virtual uint8_t getPosition() const {
        return position;
    }
    [[nodiscard]] virtual uint8_t getStartPosition() const {
        return startPosition;
    }
    [[nodiscard]] virtual uint8_t getEndPosition() const {
        return endPosition;
    }
    [[nodiscard]] virtual bool isDead() const {
        return dead;
    }
    [[nodiscard]] virtual bool isSaved() const {
        return saved;
    }
    [[nodiscard]] virtual bool isInGoalArea() const {
        return inGoalArea;
    }
    [[nodiscard]] virtual const Color& getColor() const {
        return color;
    }
    virtual void setPosition(uint8_t const value) {
        position = value;
    }
    virtual void setDead(bool const value) {
        dead = value;
    }
    virtual void setSaved(bool const value) {
        saved = value;
    }
    virtual void setInGoalArea(bool const value) {
        inGoalArea = value;
    }
    virtual bool operator==(Pawn const& other) const {
        return this->id == other.id;
    }
    [[nodiscard]] virtual std::string toString() const {
        std::string result = "Pawn " + std::to_string(getId());
        result += " at " + std::to_string(getPosition());
        result += " saved=" + std::to_string(isSaved());
        result += " dead=" + std::to_string(isDead());
        result += " inGoalArea=" + std::to_string(isInGoalArea());
        return result;
    }
};

export struct PawnHash {
    std::size_t operator()(const uint8_t key) const noexcept {
        return std::hash<uint8_t>()(key);
    }
};
