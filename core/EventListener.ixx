//
// Created by max on 4/8/26.
//

module;

export module EventListener;

import Pawn;
import Field;
import Player;

export class EventListener {
public:
    virtual ~EventListener() = default;

    virtual void onPawnKilled(const Pawn& killer, const Pawn& killed) = 0;
    virtual void onPawnRevived(const Pawn& pawn) = 0;
    virtual void onPawnSaved(const Pawn& pawn) = 0;
    virtual void onPawnMovedToGoalArea(const Pawn& pawn) = 0;
    virtual void onPawnMoved(const Pawn& pawn, const Field& from, const Field& to) = 0;
    virtual void onGameOver(const Player& player) = 0;
};
