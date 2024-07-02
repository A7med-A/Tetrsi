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

public:
    Tetramino(const Tetra TetraminiClasse[Tetra_NUM] = Tetramini, int RandomTetramino = 0);
    void draw(WINDOW *win, Tetra tetramino, int x, int y);
    void moveLeft();
    void moveRight();
    void rotate(Tetra &tetramino);
};