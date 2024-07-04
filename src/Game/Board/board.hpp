#pragma once
#include <ncurses.h>
#include "../constants.hpp"

class Board
{
protected:
    // char board[Board_HEIGHT][Board_WIDTH];
    WINDOW *playwin;

public:
    char board[Board_HEIGHT][Board_WIDTH];

    Board(WINDOW *playwin);

    void draw();

    void updateBoardFromWin();

    void Border();

    bool isOccupied(int x, int y);

    void placeTetra(Tetra tetra, int x, int y); // da modificare

    WINDOW *getWin();
};