//
// Created by max on 07.04.26.
//
module;
#include <cstdint>
#include <cstdlib>

export module Dice;

export class Dice {
private:
    uint8_t rollAccumulation = 0;
    uint8_t lastRoll = 0;
public:
    virtual ~Dice() = default;

    virtual uint8_t getRollAccumulation() {
        return rollAccumulation;
    }
    virtual uint8_t getLastRoll() {
        return lastRoll;
    }
    virtual void roll() {
        lastRoll = random() % 6; // Get a number between 0 and 5
        lastRoll++;
        rollAccumulation += lastRoll;
    }
    virtual void resetRollAccumulation() {
        rollAccumulation = 0;
    }
};
