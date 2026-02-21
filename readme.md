Implementation explanation:

    Player 1 is yellow and player 2 is red

    State strings are comprised of '0's, '1's, and '2's, where '0' = empty, '1' = player 1, and '2' = player 2
    The game's state string is stored in the grid, a method which requires setting the game tags of bits

    When trying to place a piece into a square, two conditions must be met:
    1. The square must be empty
    2. If there is a square underneath the square, it must be filled

    Wins are checked using the sliding 4x4 window method
    The window operates on the state string rather than the grid for two reasons:
    1. Doing this lets the negamax function also check wins since that funciton operates on a state string
    2. I think it's faster this way (less accessing)

    Draws are checked by checking if there are any empty squares
    The checkForDraw function also operates on the state string

    The AI uses the negamax algorithm with alpha-beta pruning
    It operates on a state string so the state can be changed without consequences
    The AI evaluates how good a state is by counting the number of feasible four in a rows and weighing them exponentially by the progess already made towards it
    Because the implementations for checking wins, checking draws, and evaluating states are all pretty slow, the AI is only permitted to search up to a depth of 3
    I personally found that any larger depth lead to a perceivable processing delay

Files modified besides Connect4.h and Connect4.cpp:

    readme.md
    - so I could write this

    .gitignore
    - so build folder doesn't commit

    CMakeLists.txt
    - so connect 4 files are linked

    ChessSquare.cpp
    - changed doubles to floats, removing warnings

    Applicaton.cpp
    - so you can play connect 4

    Game.cpp
    - so you can see which square you're highlighting
    - so you can set the AI to be either player 1 or 2

Developed and tested this project on Windows
