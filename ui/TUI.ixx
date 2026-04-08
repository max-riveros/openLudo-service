//
// Created by max on 07.04.26.
//

module;
#include <iostream>

export module UserInterface;

import Game.Default;
import Player.Default;
import EventListener.TUI;
import Game;

export class TUI {
private:
    DefaultGame* game = nullptr;

    static uint8_t selectPawn(std::vector<Pawn>& moves) {
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
    ~TUI() {
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
        const auto eventListener = TuiEventListener();
        game = new DefaultGame(pids, playerCount, eventListener);
    }

    void run() const {
        std::cout << "Running..." << std::endl;

        while (true) {
            char input = ' ';
            std::cout << std::endl << "It's " << game->getTurn().getId() << "'s turn." << std::endl;
            std::cout << "  Pawns of player:" << std::endl;
            for (const Pawn& pawn : game->getTurn().getPawns()) {
                std::cout << "  " << pawn.toString() << std::endl;
            }

            std::cout << std::endl << "  Press enter to roll dice.";
            std::cin.read(&input, 1);
            game->throwDice();
            std::cout << "  You rolled a " << std::to_string(game->getLastDiceRoll()) << "!" << std::endl;

            auto moves = game->getPossiblePawns();
            if (moves.size() == 0) {
                std::cout << "  No moves!" << std::endl;
                game->skipPlayer();
            } else {
                auto& pawn = moves[selectPawn(moves)];
                game->selectPawn(pawn.getId());
                std::cout << "  Pawn " << std::to_string(pawn.getId()) << " selected." << std::endl;

                game->doTurn();
            }

            std::cout << "End game? (y/N) ";
            std::cin.read(&input, 1);
            if (input == 'y' || input == 'Y') break;
        }
    }
};
