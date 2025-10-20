#include "Connect4.h"

// CONSTANTS
const int CONNECT4_ROWS = 6;
const int CONNECT4_COLS = 7;
const int WIN_LENGTH = 4;

Connect4::Connect4()
{
    _grid = new Grid(CONNECT4_COLS, CONNECT4_ROWS);
}

Connect4::~Connect4()
{
    delete _grid;
}

void Connect4::setUpBoard()
{
    setNumberOfPlayers(2);
        _gameOptions.rowX = CONNECT4_COLS;
        _gameOptions.rowY = CONNECT4_ROWS;
        _grid->initializeSquares(80, "square.png");

        if (gameHasAI()) {
            setAIPlayer(AI_PLAYER);
        }

        startGame();
}

Player* Connect4::checkForWinner()
{
    std::string state = stateString();
    for(int i=0; i<CONNECT4_ROWS*CONNECT4_COLS; ++i) // for each char/index
    {
        // if no owner, break
        if(state[i] == '0')
            continue;
        
        // shouldn't ever be nullptr because of condition above
        int owner = state[i];

        // check for dirs now, start with left to right
        // need to check if i is in the right pos for a left to right check
        if(getXByIndex(i) <= 3) // if i is in a good pos for left to right
        {
            // just checking with just a 
            if(owner == state[i+1]
                && owner == state[i+2] 
                && owner == state[i+3])
            {
                return ownerAt(i);
            }
            // now check the 3 chesssquares on the right of this index
            // for(int index = 0; index < WIN_LENGTH-1; ++index)
            // {
            //     // check if owner doesn't match for the next indices
            //     if(owner != ownerAt(i + index))
            //     {
            //         // invalid
                    
            //         break;
            //     }
            // }
        }

        // checking from right to left
        if(getXByIndex(i) >= 3)
        {
            if(owner == state[i-1]
                && owner == state[i-2]
                && owner == state[i-3])
            {
                return ownerAt(i);
            }
        }

        // checking from top right to bottom left
        // move downwards and left like `/`
        // check if piece is at top right of board
        if(getXByIndex(i) >=3 && getYByIndex(i) < 3)
        {
            if(owner == state[(i-1)+(CONNECT4_COLS)]
                && owner == state[(i-2)+(CONNECT4_COLS*2)]
                && owner == state[(i-3)+(CONNECT4_COLS*3)])
            {
                return ownerAt(i);
            }
        }

        // checking from top to bottom
        if(getYByIndex(i) < 3)
        {
            if(owner == state[i+(CONNECT4_COLS)]
                && owner == state[i+(CONNECT4_COLS*2)]
                && owner == state[i+(CONNECT4_COLS*3)])
            {
                return ownerAt(i);
            }
        }

        // checking from top left to bottom right
        // move downwards and right like `\`
        // check if piece is at top left of board
        if(getXByIndex(i) <=3 && getYByIndex(i) < 3)
        {
            if(owner == state[(i+1)+(CONNECT4_COLS)]
                && owner == state[(i+2)+(CONNECT4_COLS*2)]
                && owner == state[(i+3)+(CONNECT4_COLS*3)])
            {
                return ownerAt(i);
            }
        }
        
    }
    // shouldn't be recursive
    // iteratively check all 5 directions
        // right doesn't cover left
        // so need both right to left and left to right
        // bottom right should cover top left
        // down should cover up
        // bottom left should cover top right
    // iterate through each square
    // bool isWinner = true;
    // Player *owner = nullptr;

    // // stateString solution
    // for(int i=0; i<CONNECT4_ROWS*CONNECT4_COLS; ++i) // for each char/index
    // {
    //     // if no owner, break
    //     if(stateString()[i] == '0')
    //         continue;
        
    //     // shouldn't ever be nullptr because of condition above
    //     owner = ownerAt(i);

    //     // check for dirs now, start with left to right
    //     // need to check if i is in the right pos for a left to right check
    //     if(i % CONNECT4_COLS <= 3) // if i is in a good pos for left to right
    //     {
    //         // just checking with just a 
    //         if(owner == ownerAt(i+1) 
    //             && owner == ownerAt(i+2) 
    //             && owner == ownerAt(i+3))
    //         {
    //             return owner;
    //         }
    //         // now check the 3 chesssquares on the right of this index
    //         // for(int index = 0; index < WIN_LENGTH-1; ++index)
    //         // {
    //         //     // check if owner doesn't match for the next indices
    //         //     if(owner != ownerAt(i + index))
    //         //     {
    //         //         // invalid
                    
    //         //         break;
    //         //     }
    //         // }
    //     }

    //     // checking from right to left
    //     if(i % CONNECT4_COLS >= 3)
    //     {
    //         if(owner == ownerAt(i-1) 
    //             && owner == ownerAt(i-2)
    //             && owner == ownerAt(i-3))
    //         {
    //             return owner;
    //         }
    //     }

    //     // checking from top right to bottom left
    //     // move downwards and left like `/`
    //     // check if piece is at top right of board
    //     if(i%CONNECT4_COLS >=3 && i/CONNECT4_ROWS <= 3)
    //     {
    //         if(owner == ownerAt((i-1)+(CONNECT4_COLS))
    //             && owner == ownerAt((i-2)+(CONNECT4_COLS*2))
    //             && owner == ownerAt((i-3)+(CONNECT4_COLS*3)))
    //         {
    //             return owner;
    //         }
    //     }

    //     // checking from top to bottom
    //     if(i/CONNECT4_COLS < 3)
    //     {
    //         if(owner == ownerAt(i+(CONNECT4_COLS))
    //             && owner == ownerAt(i+(CONNECT4_COLS*2))
    //             && owner == ownerAt(i+(CONNECT4_COLS*3)))
    //         {
    //             return owner;
    //         }
    //     }

    //     // checking from top left to bottom right
    //     // move downwards and right like `\`
    //     // check if piece is at top left of board
    //     if(i%CONNECT4_COLS <=3 && i/CONNECT4_ROWS <= 3)
    //     {
    //         if(owner == ownerAt((i+1)+(CONNECT4_COLS))
    //             && owner == ownerAt((i+2)+(CONNECT4_COLS*2))
    //             && owner == ownerAt((i+3)+(CONNECT4_COLS*3)))
    //         {
    //             return owner;
    //         }
    //     }
        
    // }

    // object solution
    /*
        _grid->forEachSquare([&](ChessSquare* square, int x, int y)
        {
            owner = ownerAt(square->getSquareIndex());
            // cutoff early if owner doesn't exist
            if(!owner)
                return nullptr;
            // now owner exists, start checking in your dirs
            // check from left to right
            // if(owner == ownerAt(_grid->getE(x, y)->getSquareIndex()))
            // for loop might be better
            // just do it 3 times
            // get an updating square
            ChessSquare *updatingSquare = square;

            // checking from left to right
            for(int i=0; i<3; ++i)
            {
                // break immediately if column is invalid for this check
                if(square->getColumn() <= 3)
                {
                    break;
                }
                ChessSquare *nextSquare = _grid->getE(updatingSquare->getColumn(), updatingSquare->getRow());
                if(!nextSquare)
                {
                    isWinner = false;
                    break;
                }
                // if owner is square's next, continue
                // if not, break?
                // condition will be if owner is not at updatingSquare's right
                if(owner != ownerAt(nextSquare->getSquareIndex()))
                {
                    // will set isWinner to false
                    isWinner = false;
                    break;
                }
                updatingSquare = nextSquare;
            }
            // reset updatingSquare back to currentSquare
            updatingSquare = square;
            
            // check from right to left
            for(int i=0; i<3; ++i)
            {
                // break immediately if column is invalid for this check
                if(square->getColumn() >= 3)
                {
                    break;
                }
                ChessSquare *nextSquare = _grid->getW(updatingSquare->getColumn(), updatingSquare->getRow());
                if(!nextSquare)
                {
                    isWinner = false;
                    break;
                }
                if(owner != ownerAt(nextSquare->getSquareIndex()))
                {
                    isWinner = false;
                    break;
                }
                updatingSquare = nextSquare;
            }

            // check from top left to bottom right
            for(int i=0; i<3; ++i)
            {
                break;
            }
        });
        if(isWinner)
            return owner;
        else
    
    */ 
    return nullptr;
}

bool Connect4::checkForDraw()
{
    // check for winner first then check for draw
    bool isDraw = true;
    _grid->forEachSquare([&isDraw](ChessSquare* square, int x, int y)
    {
        if(!square->bit())
        {
            isDraw = false;
        }
    });
    return isDraw;
}

std::string Connect4::initialStateString()
{
    return "000000000000000000000000000000000000000000"; //6 x 7 0's
}

std::string Connect4::stateString()
{
    std::string s = initialStateString();
    _grid->forEachSquare([&](ChessSquare* square, int x, int y)
    {
        Bit *bit = square->bit();
        if(bit)
        {
            s[(y*7) + x] = std::to_string(bit->getOwner()->playerNumber()+1)[0];
            // s[(x*7) + y] = std::to_string(bit->getOwner()->playerNumber()+1)[0];
        }
    });
    
    return s;
}

void Connect4::setStateString(const std::string &s)
{
    _grid->forEachSquare([&](ChessSquare* square, int x, int y)
    {
        int index = y*CONNECT4_COLS + x;
        int playerNumber = s[index] - '0';
        if(playerNumber) 
        {
            square->setBit(PieceForPlayer(playerNumber - 1));
        }
        else 
        {
            square->setBit(nullptr);
        }
    });
}

bool Connect4::actionForEmptyHolder(BitHolder& holder)
{
    // if(holder.bit())
    //     return false;

    // got chessSquare, now have access to column and row
    ChessSquare *square = dynamic_cast<ChessSquare*>(&holder);

    if (!square) return false;

    int col = square->getColumn();
    
    Bit *bit = PieceForPlayer(getCurrentPlayer()->playerNumber() == 0 ? HUMAN_PLAYER : AI_PLAYER);
    ChessSquare *bottomSquare = _grid->getSquareByIndex(getBottomChessSquareIndex(square->getColumn()));
    // now find lowest unfilled square in current column
    // for(int i=CONNECT4_ROWS-1; i>=0; --i)
    // {
    //     ChessSquare *currentSquare = _grid->getSquare(col, i);
    //     if(currentSquare->canDropBitAtPoint(bit, currentSquare->getPosition()))
    //     {
    //         bottomSquare = currentSquare;
    //         break;
    //     }
    // }
    if(bottomSquare->bit())
        return false;
    
    if(bit)
    {
        bit->setPosition({bottomSquare->getPosition().x, 0});
        bottomSquare->dropBitAtPoint(bit, bottomSquare->getPosition());
        endTurn();
        return true;
    }
    return false;
}

int Connect4::getBottomChessSquareIndex(int col)
{   
    Bit *bit = PieceForPlayer(getCurrentPlayer()->playerNumber() == 0 ? HUMAN_PLAYER : AI_PLAYER);

    // String Implementation
    std::string state = stateString();
    // current column is currSquare->getColumn()
    for(int i=CONNECT4_ROWS-1; i>=0; --i)
    {
        if(state[(i*CONNECT4_COLS) + col] == '0')
        {
            return (i*CONNECT4_COLS) + col;
        }
    }

    // Object Implementation
    // for(int i=CONNECT4_ROWS-1; i>=0; --i)
    // {
    //     ChessSquare *currentSquare = _grid->getSquare(col, i);
    //     if(currentSquare->canDropBitAtPoint(bit, currentSquare->getPosition()))
    //     {
    //         bottomSquare = currentSquare;
    //         return bottomSquare;
    //     }
    // }
    return col;
}

// bool Connect4::actionForEmptyHolder(ChessSquare& square)
// {
//     if(square.bit())
//         return false;
//     Bit *bit = PieceForPlayer(getCurrentPlayer()->playerNumber() == 0 ? HUMAN_PLAYER : AI_PLAYER);
//     if(bit)
//     {
//         bit->setPosition({square.getPosition().x, 0});
//         bit->moveTo(square.getPosition());
//         square.setBit(bit);
//         endTurn();
//         return true;
//     }
//     return false;
// }

void Connect4::stopGame()
{
    _grid->forEachSquare([](ChessSquare* square, int x, int y)
    {
       square->destroyBit(); 
    });
}

Bit* Connect4::PieceForPlayer(const int playerNumber)
{
    Bit *bit = new Bit();

    bit->LoadTextureFromFile(playerNumber == AI_PLAYER ? "yellow.png" : "red.png");
    bit->setOwner(getPlayerAt(playerNumber == AI_PLAYER ? 1 : 0));
    return bit;
}

// ================ Code to make AI work =================

void Connect4::updateAI()
{
    std::string state = stateString();
    int bestVal = -10000;
    int bestSquare = -1;
    _lookedAt = 0;

    int alpha = -10000;
    int beta = 10000;
    // std::cout << "AI PLAYER NUM: " << _gameOptions.AIPlayer << std::endl;
    // string implementation going by col
    // going from cols left to right
    for(int i=0; i<CONNECT4_COLS; ++i)
    {
        // get bottom square idx
        int idx = getBottomChessSquareIndex(i);
        if(state[idx] == '0')
        {
            // iterative backtracking
            // make move
            state[idx] = '2';
            int moveVal = -negamax(state, 0, alpha, beta, HUMAN_PLAYER);
            // undo
            state[idx] = '0';
            // std::cout << "MOVEVAL: " << moveVal << std::endl;
            if(moveVal > bestVal)
            {
                // std::cout << "MOVEVAL: " << moveVal << " BESTVAL: " << bestVal << std::endl;
                bestSquare = idx;
                bestVal = moveVal;
            }
        }
    }
    // Object implementation and by every square
    // _grid->forEachSquare([&](ChessSquare* square, int x, int y) {
    //     int index = getIndexByCoord(x, y);
    //     // Check if cell is empty
    //     if(state[index] == '0' )
    //     {
    //         // make the move
    //         state[index] = '2';
    //         int moveVal = -negamax(state, 0, alpha, beta, HUMAN_PLAYER);
    //         // undo the move
    //         state[index] = '0';
    //         if(moveVal > bestVal)
    //         {
    //             bestSquare = square;
    //             bestVal = moveVal;
    //         }
    //     }
    // });

    // Make the best move
    std::cout << "# of operations: " << _lookedAt << std::endl;
    std::cout << "Best Square: " << bestSquare << std::endl;
    if(bestSquare != -1)
    {
        // this is what it looks like in the code, maybe just need to call actionForEmptyHolder
        if(actionForEmptyHolder(*_grid->getSquareByIndex(bestSquare))){}
    }
}

bool Connect4::isAIBoardFull(const std::string& state)
{
    return state.find('0') == std::string::npos;
}

int Connect4::evaluateAIBoard(const std::string& state)
{
    // bool isWinner = true;

    // stateString solution
    for(int i=0; i<CONNECT4_ROWS*CONNECT4_COLS; ++i) // for each char/index
    {
        // if no owner, break
        if(state[i] == '0')
            continue;
        
        // shouldn't ever be none because of condition above
        // char owner = state[i];

        // check for dirs now, start with left to right
        // need to check if i is in the right pos for a left to right check
        if(getXByIndex(i) <= 3) // if i is in a good pos for left to right
        {
            // just checking with just a 
            if(state[i] == state[i+1]
                && state[i] == state[i+2] 
                && state[i] == state[i+3])
            {
                return 100;
            }
            // now check the 3 chesssquares on the right of this index
            // for(int index = 0; index < WIN_LENGTH-1; ++index)
            // {
            //     // check if owner doesn't match for the next indices
            //     if(owner != ownerAt(i + index))
            //     {
            //         // invalid
                    
            //         break;
            //     }
            // }
        }

        // checking from right to left
        if(getXByIndex(i) >= 3)
        {
            if(state[i] == state[i-1]
                && state[i] == state[i-2]
                && state[i] == state[i-3])
            {
                return 100;
            }
        }

        // checking from top right to bottom left
        // move downwards and left like `/`
        // check if piece is at top right of board
        if(getXByIndex(i) >=3 && getYByIndex(i) < 3)
        {
            if(state[i] == state[(i-1)+(CONNECT4_COLS)]
                && state[i] == state[(i-2)+(CONNECT4_COLS*2)]
                && state[i] == state[(i-3)+(CONNECT4_COLS*3)])
            {
                return 100;
            }
        }

        // checking from top to bottom
        if(getYByIndex(i) < 3)
        {
            if(state[i] == state[i+(CONNECT4_COLS)]
                && state[i] == state[i+(CONNECT4_COLS*2)]
                && state[i] == state[i+(CONNECT4_COLS*3)])
            {
                return 100;
            }
        }

        // checking from top left to bottom right
        // move downwards and right like `\`
        // check if piece is at top left of board
        if(getXByIndex(i) <=3 && getYByIndex(i) < 3)
        {
            if(state[i] == state[(i+1)+(CONNECT4_COLS)]
                && state[i] == state[(i+2)+(CONNECT4_COLS*2)]
                && state[i] == state[(i+3)+(CONNECT4_COLS*3)])
            {
                return 100;
            }
        }
        
    }
    return 0;
}

int Connect4::negamax(std::string& state, int depth, int alpha, int beta, int playerColor)
{
    // std::cout << "negamax called" << std::endl;
    int score = evaluateAIBoard(state);
    if(depth >= 3)
        return -score;
    _lookedAt++;

    // Check if AI wins, human wins, or draw
    if(score) { 
        // A winning state is a loss for the player whose turn it is.
        // The previous player made the winning move.
        return -score; 
    }

    if(isAIBoardFull(state)) {
        return 0; // Draw
    }

    int bestVal = -1000; // Min value

    // go just by column
    for(int x=0; x<CONNECT4_COLS; ++x)
    {
        // store idx of lowest square in current column
        int idx = getBottomChessSquareIndex(x);
        if(state[idx] == '0')
        {
            // make move
            state[idx] = playerColor == HUMAN_PLAYER ? '1' : '2';
            bestVal = std::max(bestVal, -negamax(state, depth + 1, -beta, -alpha, -playerColor));
            // undo the move for ITERATIVE backtracking
            state[idx] = '0';
            alpha = std::max(alpha, bestVal);
            if(alpha > beta)
            {
                break;
            }
        }
    }
    
    return bestVal;
    // checks every square
    // for (int y = 0; y < CONNECT4_ROWS; y++) {
    //     for (int x = 0; x < CONNECT4_COLS; x++) {
    //         // store index in int
    //         int index = getIndexByCoord(x, y);
    //         // Check if cell is empty
    //         if (state[index] == '0') {
    //             // Make the move
    //             state[index] = playerColor == HUMAN_PLAYER ? '1' : '2'; // Set the cell to the current player's color
    //             bestVal = std::max(bestVal, -negamax(state, depth + 1, -beta, -alpha, -playerColor));
    //             // Undo the move for backtracking
    //             state[index] = '0';
    //             alpha = std::max(alpha, bestVal);
    //             if(alpha > beta)
    //             {
    //                 break;
    //             }
    //         }
    //     }
    // }

}

// ================ Helper Functions =================
Player *Connect4::ownerAt(int index) const
{
    ChessSquare* square = _grid->getSquare(getXByIndex(index), getYByIndex(index));
    // ChessSquare* square = _grid->getSquare(index / 3, index % 3);

    if(!square || !square->bit())
        return nullptr;
    return square->bit()->getOwner();
}

int Connect4::getXByIndex(int index) const
{
    return index % CONNECT4_COLS;
}

int Connect4::getYByIndex(int index) const
{
    return index / CONNECT4_COLS;
}

int Connect4::getIndexByCoord(int x, int y) const
{
    return y*CONNECT4_ROWS + x;
}