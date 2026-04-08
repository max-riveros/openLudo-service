//
// Created by max on 07.04.26.
//

module;

#include <cstdint>
#include <stdexcept>
#include <vector>
#include <string>

export module Player;

export import Pawn;

export class Player {
protected:
    std::string id;
    std::vector<Pawn> pawns;
public:
    virtual ~Player() = default;

    virtual const std::vector<Pawn>& getPawns() {
        return pawns;
    }
    virtual Pawn& getPawn(const uint8_t id) {
        for (Pawn& pawn: pawns) {
            if (pawn.getId() == id) return pawn;
        }
        throw std::logic_error("Pawn not found.");
    }
    [[nodiscard]] virtual const std::string& getId() const {
        return id;
    }
    [[nodiscard]] virtual const Color& getColor() const {
        return pawns.front().getColor();
    }
};
