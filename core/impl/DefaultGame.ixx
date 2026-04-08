//
// Created by max on 07.04.26.
//

module;

#include <cstdint>
#include <stdexcept>
#include <string>

export module Game.Default;

import Board.Default;
import Game;
import Player.Default;
import Pawn.Default;

const Color colors[4] = {Color::red(), Color::green(), Color::blue(), Color::yellow()};
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
            pawn.setPosition(targetPosition);
            if (targetPosition == goalAreaSize) {
                pawn.setSaved(true);
                turnsLeft++;
            }
            return true;
        }
        return false;
    }
    bool checkMurder(const Pawn& pawn, const uint8_t targetPosition) {
        Field& target = board.getField(targetPosition);
        if (!target.isSafe()) {
            auto& pawns = target.getPawns();
            if (pawns.size() != 1) {
                return false;
            }
            Pawn* other = pawns.front();
            if (other->getColor() != pawn.getColor()) {
                board.kill(*other);
                turnsLeft++;
            }
        }
        return true;
    }

protected:
    bool isTargetOutsideGoalArea(const uint8_t targetPosition) override {
        return targetPosition > goalAreaSize;
    }

    uint8_t move() override {
        if (dice.getLastRoll() == 6) turnsLeft++;

        Pawn& pawn = getSelectedPawn();

        if (pawn.isDead()) {
            board.revive(pawn);
            return 1;
        }

        uint8_t targetPosition = pawn.getPosition() + dice.getLastRoll();
        if (checkGoalZone(pawn, targetPosition)) {
            if (pawn.isSaved()) return 2;
            return 3;
        }
        targetPosition = pawn.getPosition() + dice.getLastRoll();
        targetPosition %= board.getSize();
        if (checkMurder(pawn, targetPosition)) {
            board.move(pawn, targetPosition);
            return 4;
        }

        board.move(pawn, targetPosition);
        return 0;
    }

public:
    explicit DefaultGame(const std::string* playerIds, const uint8_t playerCount) {
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
