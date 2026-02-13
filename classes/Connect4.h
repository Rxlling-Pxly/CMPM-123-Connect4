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

    std::string initialStateString() override;
    std::string stateString() override;
    void setStateString(const std::string &s) override;

    Player *checkForWinner() override;
    bool checkForDraw() override;

    bool canBitMoveFrom(Bit &bit, BitHolder &src) override;
    bool canBitMoveFromTo(Bit &bit, BitHolder &src, BitHolder &dst) override;

private:
    static const int GRID_WIDTH = 7;
    static const int GRID_HEIGHT = 6;

    static const int NUM_PLAYERS = 2;

    Grid* _grid;
};
