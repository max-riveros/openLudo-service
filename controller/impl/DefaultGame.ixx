//
// Created by max on 07.04.26.
//

module;

#include <cstdint>
#include <string>

export module Game.Default;

import Board.Default;
import Game;
import Player.Default;
import Pawn.Default;

constexpr uint8_t playerCount = 4;
const Color colors[playerCount] = {Color::red(), Color::green(), Color::blue(), Color::yellow()};
export class DefaultGame : public Game {
private:
    static constexpr std::uint8_t goalAreaSize = 4;
    DefaultBoard board;

    bool checkGoalZone(Pawn pawn, uint8_t targetPosition) {
        uint8_t goalZoneEntryPosition = pawn.getStartPosition() - 2;
        if (pawn.getPosition() <= goalZoneEntryPosition && targetPosition > goalZoneEntryPosition) {
            targetPosition -= goalZoneEntryPosition;
            if (targetPosition > goalAreaSize) return true;
            pawn.setInGoalArea(true);
            pawn.setPosition(1);
        }

        if (pawn.isInGoalArea()) {
            pawn.setPosition(targetPosition);
            if (targetPosition == goalAreaSize) {
                pawn.setSaved(true);
                turnsLeft++;
                return true;
            }
        }
        return false;
    }
    void checkMurder(Pawn pawn, const uint8_t targetPosition) {
        Field target = board.getField(targetPosition);
        if (!target.isSafe()) {
            auto pawns = target.getPawns();
            if (pawns.size() != 1) {
                return;
            }
            Pawn other = pawns.begin()->second;
            if (other.getColor() != pawn.getColor()) {
                board.kill(other);
                turnsLeft++;
            }
        }
    }

protected:
    void move() override {
        if (dice.getLastRoll() == 6) turnsLeft++;

        Pawn pawn = board.getPawn(selectedPawn);
        uint8_t targetPosition = pawn.getPosition() + dice.getLastRoll();
        targetPosition = targetPosition % board.getSize();

        if (pawn.isDead()) {
            board.revive(pawn);
            return;
        }

        if (checkGoalZone(pawn, targetPosition)) return;
        checkMurder(pawn, targetPosition);

        board.move(pawn, targetPosition);
    }

public:
    explicit DefaultGame(const std::string* playerIds, const uint8_t playerCount) {
        int lastId = 0;
        Pawn pawns[4];
        for (int i = 0; i < playerCount; i++) {
            for (int j = 0; j < 4; j++) {
                lastId++;
                pawns[j] = static_cast<Pawn>(DefaultPawn(lastId, colors[i], i*6));
            }
            auto player = static_cast<Player>(DefaultPlayer(playerIds[i], pawns));
            players.push_back(player);
        }
    }

};
