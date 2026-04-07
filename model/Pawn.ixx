//
// Created by max on 07.04.26.
//

module;
#include <cstdint>
#include <string>

export module Pawn;

export class Color {
    uint8_t r = 0;
    uint8_t g = 0;
    uint8_t b = 0;
public:
    Color(uint8_t const red, uint8_t const green, uint8_t const blue) {
        r = red;
        g = green;
        b = blue;
    }
    static Color red() {
        return {255, 0, 0};
    }
    static Color green() {
        return {0, 255, 0};
    }
    static Color blue() {
        return {0, 0, 255};
    }
    static Color yellow() {
        return {255, 255, 0};
    }
    static Color white() {
        return {255, 255, 255};
    }
    static Color black() {
        return {0, 0, 0};
    }
    virtual ~Color() = default;
    [[nodiscard]] uint8_t getRed() const {
        return r;
    }
    [[nodiscard]] uint8_t getGreen() const {
        return g;
    }
    [[nodiscard]] uint8_t getBlue() const {
        return b;
    }
    [[nodiscard]] std::string toPrettyString() const {
        std::string result;
        result += "[ Color: ";
        result += "red=" + std::to_string(r) + ", ";
        result += "green=" + std::to_string(g) + ", ";
        result += "blue=" + std::to_string(b) + " ]";
        return result;
    }
    [[nodiscard]] std::string toString() const {
        std::string result;
        result += "rgb(" + std::to_string(r) + ", ";
        result += std::to_string(g) + ", ";
        result += std::to_string(b) + ")";
        return result;
    }
    bool operator==(const Color& other) const {
        return this->r == other.r && this->g == other.g && this->b == other.b;
    }
};

export class Pawn {
protected:
    Color color = Color::white();
    bool dead = true;
    bool saved = false;
    bool inGoalArea = false;
    uint8_t id = 0;
    uint8_t position = 0;
    uint8_t startPosition = 0;

public:
    virtual ~Pawn() = default;

    virtual uint8_t getId() {
        return id;
    }
    virtual uint8_t getPosition() {
        return position;
    }
    virtual uint8_t getStartPosition() {
        return startPosition;
    }
    virtual bool isDead() {
        return dead;
    }
    virtual bool isSaved() {
        return saved;
    }
    virtual bool isInGoalArea() {
        return inGoalArea;
    }
    virtual const Color& getColor() {
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
};

export struct PawnHash {
    std::size_t operator()(const uint8_t key) const noexcept {
        return std::hash<uint8_t>()(key);
    }
};
