#include "tetramino.hpp"

Tetramino::Tetramino(const Tetra TetraminiClasse[Tetra_NUM], int RandomTetramino)
{
    srand(time(0));
    this->RandomTetramino = rand() % Tetra_NUM;
}

void Tetramino::moveLeft() {};

void Tetramino::moveRight() {};

void Tetramino::draw(WINDOW *win, Tetra tetramino, int x, int y)
{
    for (int i = 0; i < 4; i++)
    {
        for (int j = 0; j < 4; j++)
        {
            if (tetramino.shape[i][j] == '#')
            {
                mvwaddch(win, y + i, x + j, tetramino.shape[i][j]);
            }
        }
    }
};

void Tetramino::rotate(Tetra &tetramino)
{
    switch (this->RandomTetramino)
    {
    case 0:
        tetramino = TetraminiRuotati[0];

        break;
    case 1:
        tetramino = TetraminiRuotati[1];
        break;
    default:
        break;
    }
};