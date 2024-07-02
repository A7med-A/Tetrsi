#pragma once
#include <ncurses.h>
#include "../constants.hpp"

class Board
{
public:
    Board(int x, int y, int width, int height);
    void draw(WINDOW *win);
};