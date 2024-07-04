#pragma once
#include <ncurses.h>
#include <iostream>

#include "Game/Board/board.hpp"
#include "Game/Tetramino/tetramino.hpp"
#include "Game/constants.hpp"
#include "Game/Menu/menu.hpp"
#include "Game/Score/score.hpp"

class Game
{
protected:
    WINDOW *playwin, *scorewin, *menuwin;
    Board board;
    Tetramino tetramino;

public:
    Game();
    void start();
};