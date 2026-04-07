#include <iostream>
import Pawn.Default;
import Player.Default;
import Dice;
import Board.Default;

void rollDice(Dice& dice) {
    dice.roll();
    std::cout << "Dice roll: " << std::to_string(dice.getLastRoll()) << std::endl;
}

void testDice() {
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
}

void testPawn() {
    auto pawn = DefaultPawn(1, Color::red(), 0);
    std::cout << "pawn " << std::to_string(pawn.getId()) << ": " << pawn.getColor().toPrettyString() << std::endl;
}

void testPlayer() {
    Pawn pawns[4];
    pawns[0] = static_cast<Pawn>(DefaultPawn(1, Color::red(), 0));
    pawns[1] = static_cast<Pawn>(DefaultPawn(2, Color::green(), 0));
    pawns[2] = static_cast<Pawn>(DefaultPawn(3, Color::blue(), 0));
    pawns[3] = static_cast<Pawn>(DefaultPawn(4, {255, 255, 0}, 0));
    auto player = DefaultPlayer("p1", pawns);
    std::cout << "Player " << player.getId() << " has " << std::to_string(player.getPawns().size()) << " pawns." << std::endl;
}

int main() {
    testPawn();
    testPlayer();
    testDice();

    return 0;
}
