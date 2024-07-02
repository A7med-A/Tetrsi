#include "tetramino.hpp"

Tetramino::Tetramino(const Tetra TetraminiClasse[Tetra_NUM], Tetra tetramino, int RandomTetramino)
{
    srand(time(0));
    this->RandomTetramino = rand() % Tetra_NUM;
    this->tetramino = TetraminiClasse[this->RandomTetramino];
}

void Tetramino::moveLeft() {};

void Tetramino::moveRight() {};

void Tetramino::draw(WINDOW *win, int x, int y)
{
    for (int i = 0; i < 4; i++)
    {
        for (int j = 0; j < 4; j++)
        {
            if (this->tetramino.shape[i][j] == '#')
            {
                mvwaddch(win, y + i, x + j, this->tetramino.shape[i][j]);
            }
        }
    }
};

Tetra Tetramino::getTetramino()
{
    return this->tetramino;
};

void Tetramino::rotate()
{
    switch (this->RandomTetramino)
    {
    case 0:
        this->tetramino = TetraminiRuotati[0];

        break;
    case 1:
        this->tetramino = TetraminiRuotati[1];
        break;
    default:
        break;
    }
};