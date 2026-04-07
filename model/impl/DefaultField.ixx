//
// Created by max on 07.04.26.
//

module;

#include <cstdint>

export module Field.Default;
export import Field;

export class DefaultField : public Field {
public:
    DefaultField() = default;
    explicit DefaultField(uint8_t const position) {
        this->position = position;
    }
};
