#include "Connect4.h"

Connect4::Connect4() : Game()
{
    _grid = new Grid(GRID_WIDTH, GRID_HEIGHT);
}
Connect4::~Connect4()
{
    delete _grid;
}

void Connect4::setUpBoard()
{
    setNumberOfPlayers(NUM_PLAYERS);

    _gameOptions.rowX = GRID_WIDTH;
    _gameOptions.rowY = GRID_HEIGHT;
    _grid->initializeSquares(80, "square.png");

    startGame();
}
void Connect4::stopGame()
{
    _grid->forEachSquare([](ChessSquare *square, int x, int y) {
        square->destroyBit();
    });
}

std::string Connect4::initialStateString()
{
    return "NOT_IMPLEMENTED";
}
std::string Connect4::stateString()
{
    return "NOT_IMPLEMENTED";
}
void Connect4::setStateString(const std::string &s)
{
    
}

Player *Connect4::checkForWinner()
{
    return nullptr;
}
bool Connect4::checkForDraw()
{
    return false;
}

bool Connect4::canBitMoveFrom(Bit &bit, BitHolder &src)
{
    // Function not applicable to Connect 4
    return false;
}
bool Connect4::canBitMoveFromTo(Bit &bit, BitHolder &src, BitHolder &dst)
{
    // Function not applicable to Connect 4
    return false;
}
