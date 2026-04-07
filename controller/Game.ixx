//
// Created by max on 07.04.26.
//

module;

#include <cstdint>
#include <stdexcept>
#include <vector>

export module Game;

import Dice;
import Player;

export class Game {
protected:
    Dice dice;
    std::vector<Player> players;
    uint8_t currentTurn = 0;
    uint8_t turnsLeft = 1;
    uint8_t selectedPawn = 0;

    virtual bool isSelectionValid(Pawn pawn) {
        if (pawn.isDead() && dice.getLastRoll() != 6) return false;
        if (pawn.isSaved()) return false;
        if (pawn.isInGoalArea() && dice.getLastRoll() > 4 - pawn.getPosition()) return false;
        return true;
    }

    virtual void move() = 0;
    virtual void cycle() {
        if (turnsLeft != 0) turnsLeft--;
        turnsLeft = 1;
        currentTurn++;
        currentTurn = currentTurn % players.size();
    }
public:
    virtual ~Game() = default;

    virtual const std::vector<Player>& getPlayers() {
        return players;
    }
    virtual Player& getTurn() {
        return players[currentTurn];
    }
    virtual std::uint8_t getLastDiceRoll() {
        return dice.getLastRoll();
    }
    virtual bool isPawnSelected() {
        return selectedPawn == 0;
    }
    virtual bool isWaitingForSelection() {
        return !isPawnSelected() && dice.getLastRoll() != 0;
    }
    virtual bool hasMove() {
        for (const auto& pawn : getTurn().getPawns()) {
            if (isSelectionValid(pawn)) return true;
        }
        return false;
    }
    virtual void selectPawn(const uint8_t id) {
        for (Pawn pawn : getTurn().getPawns()) {
            if (pawn.getId() == id) {
                if (!isSelectionValid(pawn)) throw std::logic_error("Invalid selection!");
                selectedPawn = id;
                return;
            }
        }
        throw std::logic_error("Pawn does not exist");
    }
    virtual void doTurn() {
        if (isWaitingForSelection()) {
            move();
            dice.reset();
            selectedPawn = 0; // Deselect
            cycle();
        } else if (dice.getLastRoll() == 0) {
            dice.roll();
        } else {
            throw std::logic_error("Dice was already thrown. Please select a pawn.");
        }
    }
};
