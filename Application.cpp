#include "Application.h"
#include "imgui/imgui.h"
#include "classes/TicTacToe.h"
#include "classes/Checkers.h"
#include "classes/Othello.h"
#include "classes/Connect4.h"

namespace ClassGame {
        //
        // our global variables
        //
        Game *game = nullptr;
        bool gameOver = false;
        int gameWinner = -1;

        //
        // game starting point
        // this is called by the main render loop in main.cpp
        //
        void GameStartUp() 
        {
            game = nullptr;
        }

        //
        // game render loop
        // this is called by the main render loop in main.cpp
        //
        void RenderGame() 
        {
                ImGui::DockSpaceOverViewport();

                //ImGui::ShowDemoWindow();

                ImGui::Begin("Settings");

                if (gameOver) {
                    ImGui::Text("Game Over!");
                    ImGui::Text("Winner: %d", gameWinner);
                    if (ImGui::Button("Reset Game")) {
                        game->stopGame();
                        game->setUpBoard();
                        gameOver = false;
                        gameWinner = -1;
                    }
                }
                if (!game) {
                    if (ImGui::Button("Start Tic-Tac-Toe")) {
                        game = new TicTacToe();
                        game->setUpBoard();
                    }
                    if (ImGui::Button("Start Checkers")) {
                        game = new Checkers();
                        game->setUpBoard();
                    }
                    if (ImGui::Button("Start Othello")) {
                        game = new Othello();
                        game->setUpBoard();
                    }
                    if (ImGui::Button("Start Connect 4")) {
                        game = new Connect4();
                        game->setUpBoard();
                    }                    
                    if (ImGui::Button("Start Connect 4 AI First")) {
                        game = new Connect4();
                        game->setUpBoard();
                        game->setAIPlayer(0);
                    }
                    if (ImGui::Button("Start Connect 4 AI Second")) {
                        game = new Connect4();
                        game->setUpBoard();
                        game->setAIPlayer(1);
                    }
                } else {
                    ImGui::Text("Current Player Number: %d", game->getCurrentPlayer()->playerNumber());
                    // NOTE: ONLY INTENDED FOR CONNECT 4 BOARD vvv
                    ImGui::Text("Current Board State: \n%s\n%s\n%s\n%s\n%s\n%s", 
                        game->stateString().substr(0, 7).c_str(), 
                        game->stateString().substr(7, 7).c_str(),
                        game->stateString().substr(14, 7).c_str(),
                        game->stateString().substr(21, 7).c_str(),
                        game->stateString().substr(28, 7).c_str(),
                        game->stateString().substr(35, 7).c_str());
                }
                ImGui::End();

                ImGui::Begin("GameWindow");
                if (game) {
                    if (game->gameHasAI() && (game->getCurrentPlayer()->isAIPlayer() || game->_gameOptions.AIvsAI))
                    {
                        game->updateAI();
                    }
                    game->drawFrame();
                }
                ImGui::End();
        }

        //
        // end turn is called by the game code at the end of each turn
        // this is where we check for a winner
        //
        void EndOfTurn() 
        {
            Player *winner = game->checkForWinner();
            if (winner)
            {
                gameOver = true;
                gameWinner = winner->playerNumber();
            }
            if (game->checkForDraw()) {
                gameOver = true;
                gameWinner = -1;
            }
        }
}
