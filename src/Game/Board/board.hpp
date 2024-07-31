#pragma once
#include <ncurses.h>
#include "../constants.hpp"

class Board
{
protected:
    // char board[Board_HEIGHT][Board_WIDTH];
    WINDOW *playwin;

public:
    char FixedBoard[Board_HEIGHT][Board_WIDTH]; // la board di solo i tetramini fissi

    Board(WINDOW *playwin = NULL);

    void draw(WINDOW *test = NULL);

    void updateFixedBoardFromWin();

    void Border();

    bool checkCollision(int xAttuale, int yAttuale, int xVoluto, int yVoluto, Tetra tetra);

    bool checkRotationCollision(int xAttuale, int yAttuale, Tetra tetra, Tetra rotated);

    void placeTetra(Tetra tetra, int x, int y); // da modificare

    void clearTetra(Tetra tetra, int x, int y);

    WINDOW *getWin();

    bool checkGameOver();

    bool isLineComplete(int l);

    void removeLine(int l);
};