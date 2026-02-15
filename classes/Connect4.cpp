#include <climits>
#include "Connect4.h"

Connect4::Connect4()
{
    setNumberOfPlayers(NUM_PLAYERS);

    _grid = new Grid(GRID_WIDTH, GRID_HEIGHT);
    _grid->initializeSquares(80, "square.png");
}
Connect4::~Connect4()
{
    delete _grid;
}

void Connect4::setUpBoard()
{
    startGame();
}
void Connect4::stopGame()
{
    _grid->forEachSquare([](ChessSquare *square, int x, int y)
        { square->destroyBit(); });
}

std::string Connect4::initialStateString()
{
    return std::string(GRID_WIDTH * GRID_HEIGHT, '0');
}
std::string Connect4::stateString()
{
    return _grid->getStateString();
}

bool Connect4::actionForEmptyHolder(BitHolder &holder)
{
    if (!holder.empty())
        return false;

    ChessSquare &square = static_cast<ChessSquare &>(holder);
    ChessSquare *squareUnder = _grid->getS(square.getColumn(), square.getRow());
    if (squareUnder && squareUnder->empty())
        return false;

    Bit *piece = CreatePiece(getCurrentPlayer());
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
    bit->setGameTag(player->playerNumber() + 1);
    bit->LoadTextureFromFile(player == getPlayerAt(YELLOW_PLAYER) ? "yellow.png" : "red.png");
    return bit;
}

Player *Connect4::checkForWinner()
{
    struct Position { int x; int y; };
    static constexpr Position FourInARowsIn4x4Grid[10][4] = {
        // Horizontals
        {{0,0},{1,0},{2,0},{3,0}},
        {{0,1},{1,1},{2,1},{3,1}},
        {{0,2},{1,2},{2,2},{3,2}},
        {{0,3},{1,3},{2,3},{3,3}},
        // Verticals
        {{0,0},{0,1},{0,2},{0,3}},
        {{1,0},{1,1},{1,2},{1,3}},
        {{2,0},{2,1},{2,2},{2,3}},
        {{3,0},{3,1},{3,2},{3,3}},
        // Diagonals
        {{0,0},{1,1},{2,2},{3,3}},
        {{0,3},{1,2},{2,1},{3,0}},
    };

    for (int y = 0; y < GRID_HEIGHT - 3; y++) {
    for (int x = 0; x < GRID_WIDTH - 3; x++) {
        for (const auto& fourInARow : FourInARowsIn4x4Grid)
        {
            ChessSquare *square1 = _grid->getSquare(x + fourInARow[0].x, y + fourInARow[0].y);
            if (square1->empty()) continue;

            ChessSquare *square2 = _grid->getSquare(x + fourInARow[1].x, y + fourInARow[1].y);
            if (square2->empty()) continue;
            if (square1->bit()->getOwner() != square2->bit()->getOwner()) continue;

            ChessSquare *square3 = _grid->getSquare(x + fourInARow[2].x, y + fourInARow[2].y);
            if (square3->empty()) continue;
            if (square2->bit()->getOwner() != square3->bit()->getOwner()) continue;

            ChessSquare *square4 = _grid->getSquare(x + fourInARow[3].x, y + fourInARow[3].y);
            if (square4->empty()) continue;
            if (square3->bit()->getOwner() != square4->bit()->getOwner()) continue;

            return square1->bit()->getOwner();
        }
    }}

    return nullptr;
}
bool Connect4::checkForDraw()
{
    // Check if the board is full assuming there's no winner
    
    for (int y = 0; y < GRID_HEIGHT; y++) {
    for (int x = 0; x < GRID_WIDTH; x++) {
        if (_grid->getSquare(x, y)->empty())
            return false;
    }}

    return true;
}

void Connect4::updateAI()
{
    int bestSquareIndex = INT_MIN;
    int bestEvaluation = INT_MIN;
    std::string state = stateString();

    for (int y = 0; y < GRID_HEIGHT; y++) {
    for (int x = 0; x < GRID_WIDTH; x++) {
        int i = (y * GRID_WIDTH) + x;

        ChessSquare *square = _grid->getSquareByIndex(i);
        if (!square->empty()) continue;
        
        ChessSquare *squareUnder = _grid->getS(square->getColumn(), square->getRow());
        if (squareUnder && squareUnder->empty()) continue;

        state[i] = '0' + (getAIPlayer() + 1);
        int evaluation = -negamax(state, HUMAN_PLAYER);
        state[i] = '0';
        if (evaluation > bestEvaluation)
        {
            bestSquareIndex = i;
            bestEvaluation = evaluation;
        }
    }}

    actionForEmptyHolder(*(_grid->getSquareByIndex(bestSquareIndex)));
}
int Connect4::negamax(std::string &state, int color)
{
    return 0;
}
