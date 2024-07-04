#include "tetramino.hpp"

Tetramino::Tetramino(const Tetra TetraminiClasse[Tetra_NUM], Tetra tetramino, int RandomTetramino)
{
    srand(time(0));
    this->RandomTetramino = rand() % Tetra_NUM;
    this->tetramino = TetraminiClasse[this->RandomTetramino];
}

void Tetramino::moveLeft() {};

void Tetramino::moveRight() {};

void Tetramino::spawnTetramino(WINDOW *playwin)
{
    // spawn tetramino in the middle of the board
    int x = Board_WIDTH / 2 - 2;
    int y = 2;
    for (int i = 0; i < 4; i++)
    {
        for (int j = 0; j < 4; j++)
        {
            if (this->tetramino.shape[i][j] == '#')
            {
                mvwaddch(playwin, y + i, x + j, this->tetramino.shape[i][j]);
            }
        }
    };
    wrefresh(playwin);
}
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