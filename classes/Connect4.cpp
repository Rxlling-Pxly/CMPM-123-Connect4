#include <climits>
#include <cmath>
#include "Connect4.h"

static struct Position { int x; int y; };
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
    int winnerNumber = getWinnerNumber(stateString());
    return winnerNumber >= 0
        ? getPlayerAt(winnerNumber)
        : nullptr;
}
int Connect4::getWinnerNumber(const std::string &state)
{
    for (int y = 0; y < GRID_HEIGHT - 3; y++) {
    for (int x = 0; x < GRID_WIDTH - 3; x++) {
        for (const auto& fourInARow : FourInARowsIn4x4Grid)
        {
            char square1 = state[((y + fourInARow[0].y) * GRID_WIDTH) + (x + fourInARow[0].x)];
            if (square1 == '0') continue;

            char square2 = state[((y + fourInARow[1].y) * GRID_WIDTH) + (x + fourInARow[1].x)];
            if (square2 == '0') continue;
            if (square1 != square2) continue;

            char square3 = state[((y + fourInARow[2].y) * GRID_WIDTH) + (x + fourInARow[2].x)];
            if (square3 == '0') continue;
            if (square2 != square3) continue;

            char square4 = state[((y + fourInARow[3].y) * GRID_WIDTH) + (x + fourInARow[3].x)];
            if (square4 == '0') continue;
            if (square3 != square4) continue;

            return (square1 - '0') - 1;
        }
    }}

    return -1;
}

bool Connect4::checkForDraw()
{
    return checkForDraw(stateString());
}
bool Connect4::checkForDraw(const std::string &state)
{
    // Check if the board is full assuming there's no winner
    
    for (int y = 0; y < GRID_HEIGHT; y++) {
    for (int x = 0; x < GRID_WIDTH; x++) {
        if (state[(y * GRID_WIDTH) + x] == '0')
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
        int evaluation = -negamax(state, 0, INT_MIN, INT_MAX, HUMAN_PLAYER);
        state[i] = '0';
        if (evaluation > bestEvaluation)
        {
            bestSquareIndex = i;
            bestEvaluation = evaluation;
        }
    }}

    actionForEmptyHolder(*(_grid->getSquareByIndex(bestSquareIndex)));
}
int Connect4::negamax(std::string &state, int depth, int alpha, int beta, int color)
{
    if (getWinnerNumber(state) >= 0)
        return color * (INT_MAX - depth);

    if (checkForDraw(state))
        return 0;

    if (depth >= MAX_AI_DEPTH)
        return color * getEvaluation(state);
    
    return 0;
}
int Connect4::getEvaluation(std::string &state)
{
    int result = 0;
    int maximizingPlayerNumber = getAIPlayer() + 1;

    for (int y = 0; y < GRID_HEIGHT - 3; y++) {
    for (int x = 0; x < GRID_WIDTH - 3; x++) {
        for (const auto& fourInARow : FourInARowsIn4x4Grid)
        {
            int numMinimizingPlayerNumbers = 0;
            int numMaximizingPlayerNumbers = 0;

            for (const auto& [dx, dy] : fourInARow)
            {
                char square = state[((y + dy) * GRID_WIDTH) + (x + dx)];
                if (square == '0') continue;

                int number = square - '0';
                if (number == maximizingPlayerNumber) numMaximizingPlayerNumbers++;
                else numMinimizingPlayerNumbers++;
            }

            if (numMinimizingPlayerNumbers > 0 && numMaximizingPlayerNumbers == 0)
            {
                if      (numMinimizingPlayerNumbers == 1) result -= 1;
                else if (numMinimizingPlayerNumbers == 2) result -= 10;
                else if (numMinimizingPlayerNumbers == 3) result -= 100;
            }
            else if (numMaximizingPlayerNumbers > 0 && numMinimizingPlayerNumbers == 0)
            {
                if      (numMaximizingPlayerNumbers == 1) result += 1;
                else if (numMaximizingPlayerNumbers == 2) result += 10;
                else if (numMaximizingPlayerNumbers == 3) result += 100;
            }
        }
    }}

    return result;
}
