//
// Created by max on 07.04.26.
//

module;
#include <iostream>

export module UI.Terminal;

import Game.Default;
import Player.Default;
import UI;

export class TUI : public UI {
private:
    DefaultGame* game = nullptr;

    static uint8_t selectPawn(std::vector<Pawn>& moves) {
        if (moves.size() == 1) return 0;
        std::cout << "  Please select a pawn (1-" << moves.size() << "):" << std::endl;
        for (int i = 0; i < moves.size(); i++) {
            auto pawn = moves[i];
            std::cout << "    " << std::to_string(i+1) << ". " << pawn.toString() << std::endl;
        }
        int pawnNumber = 0;
        std::cin >> pawnNumber;
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

        if (pawnNumber > moves.size() || pawnNumber == 0) {
            std::cout << "  That is not a valid pawn!" << std::endl;
            selectPawn(moves);
        }
        pawnNumber--;

        return pawnNumber;
    }
public:
    ~TUI() override {
        if (game == nullptr) delete game;
    }

    void init() {
        int playerCount = 0;
        std::cout << "Please provide the number of players: ";
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

    }
    void onPlayerTurn(const Player &player) override {

    }
    void onPlayerSkipped() override {

    }
    void onWaitingForDice() override {

    }
    void onDiceRolled() override {

    }
    void onWaitingForSelect() override {

    }
    void onSelected() override {

    }

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
    void onGameOver(const Player& player) override {
        std::cout << "Game Over! " << player.getId() << " saved all pawns!" << std::endl;
    }
};
