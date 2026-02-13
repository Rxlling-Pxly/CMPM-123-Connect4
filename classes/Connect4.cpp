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

bool Connect4::actionForEmptyHolder(BitHolder &holder)
{
    if (!holder.empty())
        return false;

    ChessSquare &square = static_cast<ChessSquare&>(holder);
    int squareUnderX = square.getColumn();
    int squareUnderY = square.getRow() + 1;
    if (_grid->isValid(squareUnderX, squareUnderY) && _grid->getSquare(squareUnderX, squareUnderY)->empty())
        return false;

    Bit* piece = CreatePiece(getCurrentPlayer());
    piece->setPosition(holder.getPosition());
    holder.setBit(piece);
    holder.setHighlighted(false);
    endTurn();
    return true;
}
Bit *Connect4::CreatePiece(Player *player)
{
    Bit *bit = new Bit();
    bit->setOwner(player);
    bit->setGameTag(player->playerNumber());
    bit->LoadTextureFromFile(player == getPlayerAt(YELLOW_PLAYER) ? "yellow.png" : "red.png");
    return bit;
}

std::string Connect4::initialStateString()
{
    return std::string(GRID_WIDTH * GRID_HEIGHT, '0');
}
std::string Connect4::stateString()
{
    return _grid->getStateString();
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
