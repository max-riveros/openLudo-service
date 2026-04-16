//
// Created by max on 4/8/26.
//

module;

#include <cstdint>

export module UI;

export import Pawn;
export import Field;
export import Player;

export class UI {
public:
    virtual ~UI() = default;

    virtual void start() = 0;

    virtual void onGameStart() = 0;
    virtual void onPlayerTurn(const Player& player) = 0;
    virtual void onWaitingForDice() = 0;
    virtual void onDiceRolled(uint8_t value) = 0;
    virtual void onWaitingForSelect() = 0;
    virtual void onSelected(const Pawn& pawn) = 0;
    virtual void onPlayerSkipped() = 0;
    
    virtual void onPawnKilled(const Pawn& killer, const Pawn& killed) = 0;
    virtual void onPawnRevived(const Pawn& pawn) = 0;
    virtual void onPawnSaved(const Pawn& pawn) = 0;
    virtual void onPawnMovedToGoalArea(const Pawn& pawn) = 0;
    virtual void onPawnMoved(const Pawn& pawn, const Field& from, const Field& to) = 0;
    virtual void onGameOver(const Player& player) = 0;
};
