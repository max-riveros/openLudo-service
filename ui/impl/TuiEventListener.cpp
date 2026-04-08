//
// Created by max on 4/8/26.
//

module;

#include <iostream>

export module EventListener.TUI;

import Pawn;
import Field;
export import EventListener;

export class TuiEventListener : public EventListener {
public:
    void onPawnKilled(const Pawn& killer, const Pawn& killed) override {
        std::cout << "Pawn " << std::to_string(killer.getId())
            << " killed Pawn " << std::to_string(killed.getId()) << "!" << std::endl;
    }
    void onPawnRevived(const Pawn& pawn) override {
        std::cout << "Pawn " << std::to_string(pawn.getId()) << " has been revived!" << std::endl;
    }
    void onPawnSaved(const Pawn& pawn) override {
        std::cout << "Pawn " << std::to_string(pawn.getId()) << " has been saved!" << std::endl;
    }
    void onPawnMovedToGoalArea(const Pawn& pawn) override {
        std::cout << "Pawn " << std::to_string(pawn.getId()) << " moved to the "
            << std::to_string(pawn.getPosition() + 1) << ". field in the goal area!" << std::endl;
    }
    void onPawnMoved(const Pawn& pawn, const Field& from, const Field& to) override {
        std::cout << "Pawn " << std::to_string(pawn.getId()) << " moved from "
            << std::to_string(from.getPosition()) << " to " << std::to_string(to.getPosition()) << "!" << std::endl;
    }
};
