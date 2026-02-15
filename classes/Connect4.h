#pragma once
#include "Game.h"

class Connect4 : public Game
{
public:
    static const unsigned int YELLOW_PLAYER = 0;
    static const unsigned int RED_PLAYER = 1;

    Connect4();
    ~Connect4();

    void setUpBoard() override;
    void stopGame() override;

    bool gameHasAI() override { return _gameOptions.AIPlaying; }
    Grid *getGrid() { return _grid; }

    std::string initialStateString() override;
    std::string stateString() override;
    void setStateString(const std::string &s) {} // not implemented, forced to override

    bool actionForEmptyHolder(BitHolder &holder) override;
    Player *checkForWinner() override;
    bool checkForDraw() override;

    void updateAI() override;

    bool canBitMoveFrom(Bit &bit, BitHolder &src) { return false; } // not applicable, forced to override
    bool canBitMoveFromTo(Bit &bit, BitHolder &src, BitHolder &dst) { return false; } // not applicable, forced to override

private:
    static const unsigned int GRID_WIDTH = 7;
    static const unsigned int GRID_HEIGHT = 6;

    static const unsigned int NUM_PLAYERS = 2;

    Grid* _grid = nullptr;

    Bit *CreatePiece(Player *player);

    int negamax(std::string &state, int color);
};
