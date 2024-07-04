#pragma once
#include <ncurses.h>
#include "../constants.hpp"

class Board
{
protected:
    // char board[Board_HEIGHT][Board_WIDTH];
    WINDOW *playwin;

public:
    char board[Board_HEIGHT][Board_WIDTH]; // per ora inutile

    Board(WINDOW *playwin = NULL);

    void draw();

    void updateBoardFromWin();

    void Border();

    bool checkCollision(int xAttuale, int yAttuale, int xVoluto, int yVoluto, Tetra tetra);

    void placeTetra(Tetra tetra, int x, int y); // da modificare

    void clearTetra(Tetra tetra, int x, int y);

    WINDOW *getWin();
};