//
// Created by max on 07.04.26.
//

module;

#include <cstdint>
#include <stdexcept>
#include <string>
#include <map>
#include <ranges>

export module Game.Default;

import Board.Default;
import Game;
import Player.Default;
import Pawn.Default;
import UI;

constexpr Color colors[4] = {RED, BLUE, YELLOW, GREEN};
export class DefaultGame : public Game {
private:
    static constexpr std::uint8_t goalAreaSize = 4;
    static constexpr std::int8_t goalAreaEntryOffset = -2;
    DefaultBoard board;

    bool checkGoalZone(Pawn& pawn, uint8_t targetPosition) {
        if (isTargetPastEnd(pawn)) {
            targetPosition -= pawn.getEndPosition(); // Target position inside goal area
            targetPosition--;
            if (isTargetOutsideGoalArea(targetPosition)) throw std::logic_error("Selected pawn would move out of bounds!");
            pawn.setInGoalArea(true); // Move pawn inside goal area
        }

        if (pawn.isInGoalArea()) {
            if (targetPosition == goalAreaSize) {
                pawn.setSaved(true);
                turnsLeft++;
                ui->onPawnSaved(pawn);
                if (hasPlayerWon()) {
                    ui->onGameOver(getTurn());
                }
            } else {
                pawn.setPosition(targetPosition);
                ui->onPawnMovedToGoalArea(pawn);
            }
            return true;
        }
        return false;
    }
    Pawn* checkMurder(const Pawn& pawn, const uint8_t targetPosition) {
        Field& target = board.getField(targetPosition);
        if (!target.isSafe()) {
            auto& pawns = target.getPawns();
            if (pawns.size() != 1) {
                return nullptr;
            }
            Pawn* other = pawns.front();
            if (other->getColor() != pawn.getColor()) {
                board.kill(*other);
                turnsLeft++;
                return other;
            }
        }
        return nullptr;
    }

protected:
    bool isTargetOutsideGoalArea(const uint8_t targetPosition) override {
        return targetPosition > goalAreaSize;
    }

    void move() override {
        if (dice.getLastRoll() == 6) turnsLeft++;

        Pawn& pawn = getSelectedPawn();

        if (pawn.isDead()) {
            board.revive(pawn);
            ui->onPawnRevived(pawn);
            return;
        }

        uint8_t targetPosition = pawn.getPosition() + dice.getLastRoll();
        if (checkGoalZone(pawn, targetPosition)) return;
        targetPosition = pawn.getPosition() + dice.getLastRoll();
        targetPosition %= board.getSize();

        ui->onPawnMoved(pawn, board.getField(pawn.getPosition()), board.getField(targetPosition));
        Pawn* killed = checkMurder(pawn, targetPosition);
        if (killed != nullptr) {
            ui->onPawnKilled(pawn, *killed);
        }

        board.move(pawn, targetPosition);
    }

public:
    explicit DefaultGame(const std::map<std::string, Color>& players, UI* ui) : Game(ui) {
        int playerCounter = 0;
        for (const auto [key, value] : players) {
            Pawn pawns[4];
            for (int pawn = 0; pawn < 4; pawn++) {
                const uint8_t startPosition = 13 * value; // Use int value of enum
                int16_t endPosition = startPosition + goalAreaEntryOffset;
                endPosition %= board.getSize();
                if (endPosition < 0) {
                    endPosition = board.getSize() + endPosition;
                }
                const uint8_t pawnId = playerCounter*4 + pawn;
                pawns[pawn] = static_cast<Pawn>(DefaultPawn(pawnId, value, startPosition, endPosition));
            }
            auto player = static_cast<Player>(DefaultPlayer(key, pawns));
            this->players.push_back(player);
            playerCounter++;
        }
    }
    explicit DefaultGame(const std::string* playerIds, const uint8_t playerCount, UI* ui) : Game(ui) {
        int lastId = 0;
        Pawn pawns[4];
        for (int i = 0; i < playerCount; i++) {
            for (int j = 0; j < 4; j++) {
                // Add pawns of player
                lastId++;
                uint8_t startPosition = i*13;
                int16_t endPosition = startPosition + goalAreaEntryOffset;
                endPosition %= board.getSize();
                if (endPosition < 0) {
                    endPosition = board.getSize() + endPosition;
                }
                pawns[j] = static_cast<Pawn>(DefaultPawn(lastId, colors[i], startPosition, endPosition));
            }
            auto player = static_cast<Player>(DefaultPlayer(playerIds[i], pawns));
            players.push_back(player);
        }
    }
};
