#pragma once
#include "../constants.hpp"
#include "random"
#include <iostream>
#include "ctime"
#include "../Board/board.hpp"

#include <ncurses.h>

class Tetramino
{
protected:
    int RandomTetramino;
    Tetra tetramino;
    int x, y;
    Tetra RotatdTetramino;

public:
    Tetramino(const Tetra TetraminiClasse[Tetra_NUM] = Tetramini, Tetra tetramino = Tetramini[0], int RandomTetramino = 0);
    void spawnTetramino(WINDOW *playwin);
    int getX();
    int getY();

    bool checkBottomCollision(Board board); // serve per il tetramino quando tocca il fondo

    Tetra getTetramino();
    void rotate(Board board);
    void moveDown(Board board);
    void moveLeft(Board board);
    void moveRight(Board board);
};