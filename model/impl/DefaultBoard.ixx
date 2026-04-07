//
// Created by max on 07.04.26.
//

module;

#include <cstdint>
#include <stdexcept>

export module Board.Default;

export import Board;
export import Field.Default;

export class DefaultBoard : Board {
private:
    static constexpr std::uint8_t size = 24;
    DefaultField fields[size] = {};
public:
    explicit DefaultBoard() {
        for (int i = 0; i < size; i++) {
            fields[i] = DefaultField(i);
        }
    }
    uint8_t getSize() override { return size; }
    const Field* getFields() override { return fields; }
    const Field& getField(const uint8_t position) override {
        if (position < 0) throw std::out_of_range("Tried to access a Field that's not on the board!");
        if (position >= size) throw std::out_of_range("Tried to access a Field that's not on the board!");
        return fields[position];
    }
};
