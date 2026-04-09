//
// Created by max on 07.04.26.
//
module;
#include <cstdint>
#include <random>
#include <chrono>

export module Dice;

export class Dice {
private:
    uint8_t rollAccumulation = 0;
    uint8_t lastRoll = 0;

    static std::mt19937_64& global_rng() {
        thread_local std::mt19937_64 rng = []{
            std::random_device rd;
            uint64_t a = (uint64_t(rd()) << 32) ^ rd();
            uint64_t b = uint64_t(std::chrono::high_resolution_clock::now().time_since_epoch().count());
            std::seed_seq seq{uint32_t(a), uint32_t(a>>32), uint32_t(b), uint32_t(b>>32)};
            return std::mt19937_64(seq);
        }();
        return rng;
    }

    static int random_int(int low, int high) {
        auto& rng = global_rng();
        std::uniform_int_distribution d(low, high);
        return d(rng);
    }

public:
    virtual ~Dice() = default;

    virtual uint8_t getRollAccumulation() {
        return rollAccumulation;
    }
    virtual uint8_t getLastRoll() {
        return lastRoll;
    }
    virtual void roll() {
        lastRoll = random_int(1, 6); // Get a number between 0 and 5
        rollAccumulation += lastRoll;
    }
    virtual void reset() {
        lastRoll = 0;
        rollAccumulation = 0;
    }
    virtual void resetRollAccumulation() {
        rollAccumulation = 0;
    }
};
