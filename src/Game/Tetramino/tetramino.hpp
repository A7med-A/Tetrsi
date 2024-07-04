#pragma once
#include "../constants.hpp"
#include "random"
#include <iostream>
#include "ctime"

#include <ncurses.h>

class Tetramino
{
protected:
    int RandomTetramino;
    Tetra tetramino;

public:
    Tetramino(const Tetra TetraminiClasse[Tetra_NUM] = Tetramini, Tetra tetramino = Tetramini[0], int RandomTetramino = 0);
    void spawnTetramino(WINDOW *playwin);
    void moveLeft();
    void moveRight();
    Tetra getTetramino();
    void rotate();
};