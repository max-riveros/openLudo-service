//
// Created by max on 07.04.26.
//

module;

#include <cstdint>
#include <stdexcept>
#include <vector>

export module Game;

import UI;
import Dice;
import Player;

export class Game {
protected:
    UI *ui;
    Dice dice;
    std::vector<Player> players;
    uint8_t currentTurn = 0;
    uint8_t turnsLeft = 1;
    uint8_t selectedPawn = 0;

    explicit Game(UI* ui) {
        this->ui = ui;
    }

    virtual bool isTargetOutsideGoalArea(uint8_t targetPosition) = 0;
    virtual bool isTargetPastEnd(const Pawn& pawn) {
        return pawn.getPosition() <= pawn.getEndPosition() && dice.getLastRoll() + pawn.getPosition() > pawn.getEndPosition();
    }

    virtual bool isSelectionValid(const Pawn& pawn) {
        if (pawn.isDead() && dice.getLastRoll() != 6) return false;
        if (pawn.isSaved()) return false;
        uint8_t targetPosition = pawn.getPosition() + dice.getLastRoll();
        if (pawn.isInGoalArea() && isTargetOutsideGoalArea(targetPosition)) return false;
        if (isTargetPastEnd(pawn)) {
            targetPosition -= pawn.getEndPosition();
            targetPosition--;
            if (isTargetOutsideGoalArea(targetPosition)) return false;
        }
        return true;
    }

    virtual void move() = 0;
    virtual void cycle() {
        if (turnsLeft != 0) {
            turnsLeft--;
        } else {
            currentTurn++;
            currentTurn %= players.size();
            ui->onPlayerTurn(getTurn());
        }
        ui->onWaitingForDice();
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
        return selectedPawn != 0;
    }
    virtual bool isWaitingForSelection() {
        return !isPawnSelected() && dice.getLastRoll() != 0;
    }
    virtual Pawn& getSelectedPawn() {
        return getTurn().getPawn(selectedPawn);
    }
    virtual std::vector<Pawn> getPossiblePawns() {
        std::vector<Pawn> result;
        for (const Pawn& pawn : getTurn().getPawns()) {
            if (isSelectionValid(pawn)) result.push_back(pawn);
        }
        return result;
    }
    virtual bool hasPlayerWon() {
        for (const Pawn& pawn : getTurn().getPawns()) {
            if (!pawn.isSaved()) return false;
        }
        return true;
    }
    virtual bool hasMove() {
        for (const Pawn& pawn : getTurn().getPawns()) {
            if (isSelectionValid(pawn)) return true;
        }
        return false;
    }
    virtual void doTurn() {
        if (!isWaitingForSelection()) {
            move();
            dice.reset();
            selectedPawn = 0; // Deselect
            cycle();
            return;
        }

        throw std::logic_error("Please select the pawn you want to move.");
    }
    virtual void selectPawn(const uint8_t id) {
        for (const Pawn& pawn : getTurn().getPawns()) {
            if (pawn.getId() == id) {
                if (!isSelectionValid(pawn)) throw std::logic_error("Invalid selection!");
                selectedPawn = id;
                ui->onSelected(pawn);
                doTurn();
                return;
            }
        }
        throw std::logic_error("Pawn does not exist");
    }
    virtual void skipPlayer() {
        ui->onPlayerSkipped();
        dice.reset();
        turnsLeft = 0;
        cycle();
    }
    virtual void rollDice() {
        if (dice.getLastRoll() == 0) {
            dice.roll();
            ui->onDiceRolled();
            if (!getPossiblePawns().empty()) {
                ui->onWaitingForSelect();
            } else {
                skipPlayer();
            }
            return;
        }

        throw std::logic_error("Dice was already thrown. Please select a pawn.");
    }
    virtual void start() {
        ui->onGameStart();
        ui->onPlayerTurn(getTurn());
        ui->onWaitingForDice();
    }
};
