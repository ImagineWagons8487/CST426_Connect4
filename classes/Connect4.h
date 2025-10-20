#pragma once
#include "Game.h"

class Connect4 : public Game
{
    public:
        Connect4();
        ~Connect4();
        
        void        setUpBoard() override;
        Player*     checkForWinner() override;
        bool        checkForDraw() override;

        // State Strings
        std::string initialStateString() override;
        std::string stateString() override;
        void        setStateString(const std::string &s) override;

        // click on any holder in a column and drop into said column
        bool        actionForEmptyHolder(BitHolder &holder) override;
        int         getBottomChessSquareIndex(int col);
        // bool        actionForEmptyHolder(ChessSquare &square);
        void        stopGame() override; 
        Grid*       getGrid() override {return _grid;}
        // ===============  Shouldn't Be Needed  ===================
        bool        canBitMoveFrom(Bit& bit, BitHolder& src) override {return false;}
        bool        canBitMoveFromTo(Bit &bit, BitHolder &src, BitHolder &dst) override {return false;}
        // =========================================================
        
        // AI stuff
        void        updateAI() override;
        bool        gameHasAI() override { return _gameOptions.AIPlaying; }
        // AI Helpers
        bool isAIBoardFull(const std::string& state);
        int evaluateAIBoard(const std::string& state);

    private:
        Bit*        PieceForPlayer(const int playerNumber);
        Player*     ownerAt(int index) const;
        int         getXByIndex(int index) const;
        int         getYByIndex(int index) const;
        int         getIndexByCoord(int x, int y) const;
        int         negamax(std::string& state, int depth, int alpha, int beta, int playerColor);
        
        int         _lookedAt;
        Grid*       _grid;
    // `static` allows for a second copy of a function in the same file
    // pieceForPlayer
    // setUpBoard
    // void TicTacToe::setUpBoard()
    // {
    //     setNumberOfPlayers(2);
    //     _gameOptions.rowX = CONNECT4_COLS;
    //     _gameOptions.rowY = CONNECT4_ROWS;
    //     _grid->initializeSquares(80, "square.png");

    //     if (gameHasAI()) {
    //         setAIPlayer(AI_PLAYER);
    //     }

    //     startGame();
    // }
    // isColumnFull
    // ownerAt
    // checkDirection
    // checkForWinner
    // checkForDraw
    // initialStateString
    // stateString
    // setStateString
    // copy updateAI code down from tictactoe and paste into connect 4 first, including h code then fix accordingly
        // should work out of the boxd
        // also include the button to switch from AI to Player, vice versa    
};