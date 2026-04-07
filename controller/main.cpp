#include <iostream>
import DefaultPawn;
import Dice;

void rollDice(Dice& dice) {
    dice.roll();
    std::cout << "Dice roll: " << std::to_string(dice.getLastRoll()) << std::endl;
}

int main() {
    auto pawn = DefaultPawn(1, Color::red());
    std::cout << "pawn " << std::to_string(pawn.getId()) << ": " << pawn.getColor().toPrettyString() << std::endl;

    Dice dice;
    for (int i = 1; i <= 5; i++) {
        rollDice(dice);
    }
    std::cout << "Dice total: " << std::to_string(dice.getRollAccumulation()) << std::endl;
    dice.resetRollAccumulation();
    for (int i = 1; i <= 5; i++) {
        rollDice(dice);
    }
    std::cout << "Dice total: " << std::to_string(dice.getRollAccumulation()) << std::endl;

    return 0;
}
