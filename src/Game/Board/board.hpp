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

    void updateWinFromFixedBoard(); // risolve il problema di avere solo una window senza la test window

    void Border();

    bool checkCollision(int xAttuale, int yAttuale, int xVoluto, int yVoluto, Tetra tetra);

    bool checkRotationCollision(int xAttuale, int yAttuale, Tetra tetra, Tetra rotated);

    void placeTetra(Tetra tetra, int x, int y); // da modificare

    void clearTetra(Tetra tetra, int x, int y);

    void resetBoardAndWin();

    WINDOW *getWin();

    bool checkGameOver();

    bool isLineComplete(int l);

    void removeLine(int l);

    int clearLines();
};