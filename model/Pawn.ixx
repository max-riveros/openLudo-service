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
};

export class Pawn {
protected:
    uint8_t id = 0;
    bool dead = true;
    bool saved = false;
    bool inGoalArea = false;
    Color color = Color::white();

public:
    virtual ~Pawn() = default;

    virtual uint8_t getId() {
        return id;
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
    };
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

export template<>
struct std::hash<Pawn> {
    std::size_t operator()(Pawn& pawn) const noexcept {
        return std::hash<uint8_t>()(pawn.getId());
    }
};
