#pragma once
#include "Game.h"

class Connect4 : public Game
{
public:
    Connect4();
    ~Connect4();

    Grid *getGrid() { return _grid; }

    void setUpBoard() override;
    void stopGame() override;

    bool actionForEmptyHolder(BitHolder &holder) override;

    std::string initialStateString() override;
    std::string stateString() override;
    void setStateString(const std::string &s) {} // not implemented

    Player *checkForWinner() override;
    bool checkForDraw() override;

    bool canBitMoveFrom(Bit &bit, BitHolder &src) { return false; } // not applicable
    bool canBitMoveFromTo(Bit &bit, BitHolder &src, BitHolder &dst) { return false; } // not applicable

private:
    static const int GRID_WIDTH = 7;
    static const int GRID_HEIGHT = 6;

    static const int NUM_PLAYERS = 2;
    static const int YELLOW_PLAYER = 0;
    static const int RED_PLAYER = 1;

    Grid* _grid;

    Bit *CreatePiece(Player *player);
};
