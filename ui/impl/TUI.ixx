//
// Created by max on 07.04.26.
//

module;

#include <iostream>
#include <print>

export module UI.Terminal;

import Game.Default;
import Player.Default;
import UI;

export class TUI : public UI {
private:
    DefaultGame* game = nullptr;

    static uint8_t selectPawn(const std::vector<Pawn>& moves) {
        if (moves.size() == 1) return 0;
        std::println("  Please select a pawn (1-{}):", moves.size());
        for (int i = 0; i < moves.size(); i++) {
            auto pawn = moves[i];
            std::println("    {}: [{}]", i+1, pawn.toString());
        }
        int pawnNumber = 0;
        std::cin >> pawnNumber;
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

        if (pawnNumber > moves.size() || pawnNumber == 0) {
            std::println("  That is not a valid pawn!");
            return selectPawn(moves);
        }
        pawnNumber--;

        return pawnNumber;
    }
    static void clrscr() {
        std::cout << std::string(22, '\n'); // Print a bunch of linebreaks
                                                // in case the terminal doesn't support ANSI escape sequences
        std::cout << "\033[2J\033[1;1H"; // Clear screen using ANSI escape sequences
    }
public:
    ~TUI() override {
        if (game == nullptr) delete game;
    }

    void init() {
        clrscr();
        std::print("Starting game...");
        int playerCount = 0;
        std::print("Please provide the number of players: ");
        std::cin >> playerCount;
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        std::string pids[playerCount];
        for (uint8_t i = 0; i < playerCount; i++) {
            pids[i] = "player_" + std::to_string(i+1);
        }
        game = new DefaultGame(pids, playerCount, this);
    }

    void start() const override {
        game->start();
    }

    void onGameStart() override {
        std::println("Started game!");
    }
    void onPlayerTurn(const Player& player) override {
        std::print("  Please press enter to continue.");
        char ignored[1];
        std::cin.getline(ignored, 1);

        clrscr();
        std::println("It's {}'s turn.", player.getId());
    }
    void onPlayerSkipped() override {
        std::println("  No moves!");
    }
    void onWaitingForDice() override {
        std::println();
        std::print("  Please press enter to roll the dice.");
        char ignored[1];
        std::cin.getline(ignored, 1);
        game->rollDice();
    }
    void onDiceRolled(uint8_t value) override {
        std::println("  Rolled a {}!", value);
    }
    void onWaitingForSelect() override {
        const auto moves = game->getPossiblePawns();
        const uint8_t id = moves[selectPawn(moves)].getId();
        game->selectPawn(id);
    }
    void onSelected(const Pawn& pawn) override {
        std::println("  Selected [{}]!", pawn.toString());
    }

    void onPawnKilled(const Pawn& killer, const Pawn& killed) override {
        std::println("  Pawn {} killed Pawn {}!", killer.getId(), killed.getId());
    }
    void onPawnRevived(const Pawn& pawn) override {
        std::println("  Pawn {} has been revived!", pawn.getId());
    }
    void onPawnSaved(const Pawn& pawn) override {
        std::println("  Pawn {} has been saved!", pawn.getId());
    }
    void onPawnMovedToGoalArea(const Pawn& pawn) override {
        std::println("  Pawn {} moved to field {} in the goal area!", pawn.getId(), pawn.getPosition());
    }
    void onPawnMoved(const Pawn& pawn, const Field& from, const Field& to) override {
        std::println("  Pawn moved from {} to {}!", from.getPosition(), to.getPosition());
    }
    void onGameOver(const Player& player) override {
        std::println();
        std::println("Game over! {} saved all pawns!", player.getId());
    }
};
