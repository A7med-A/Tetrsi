#include "tetramino.hpp"

Tetramino::Tetramino(const Tetra TetraminiClasse[Tetra_NUM], Tetra tetramino, int RandomTetramino)
{
    srand(time(0));
    this->RandomTetramino = rand() % Tetra_NUM;
    this->tetramino = TetraminiClasse[this->RandomTetramino];
    this->x = Board_WIDTH / 2 - 2;
    this->y = 0;
}

int Tetramino::getX()
{
    return this->x;
};

int Tetramino::getY()
{
    return this->y;
};

void Tetramino::spawnTetramino(WINDOW *playwin)
{
    // spawn tetramino in the middle of the board
    this->RandomTetramino = rand() % Tetra_NUM;
    this->tetramino = Tetramini[this->RandomTetramino];
    this->x = Board_WIDTH / 2 - 2;
    this->y = 0;

    for (int i = 0; i < 4; i++)
    {
        for (int j = 0; j < 4; j++)
        {
            if (this->tetramino.shape[i][j] == '#')
            {
                mvwaddch(playwin, this->y + i, this->x + j, this->tetramino.shape[i][j]);
            }
        }
    };
    wrefresh(playwin);
}
Tetra Tetramino::getTetramino()
{
    return this->tetramino;
};

void Tetramino::rotate(Board board) {

};

void Tetramino::moveDown(Board board)
{

    int actualX = this->x;
    int actualY = this->y;

    // check if the next position is occupied
    if (board.checkCollision(getX(), getY(), actualX, actualY + 1, this->tetramino))
    {
        // fisso il tetramino
        board.placeTetra(this->tetramino, actualX, actualY);
    }
    else
    {
        // move the tetramino down
        board.clearTetra(this->tetramino, actualX, actualY);

        this->y++;
        board.placeTetra(this->tetramino, this->x, this->y);
    }
};

void Tetramino::moveLeft(Board board)
{
    int actualX = this->x;
    int actualY = this->y;

    if (board.checkCollision(getX(), getY(), actualX - 1, actualY, this->tetramino))
    {
        // fisso il tetramino
        board.placeTetra(this->tetramino, actualX, actualY);
    }
    else
    {
        // move the tetramino left
        board.clearTetra(this->tetramino, actualX, actualY);

        this->x--;
        board.placeTetra(this->tetramino, this->x, this->y);
    }
};

void Tetramino::moveRight(Board board)
{
    int actualX = this->x;
    int actualY = this->y;

    if (board.checkCollision(getX(), getY(), actualX + 1, actualY, this->tetramino))
    {
        // fisso il tetramino
        board.placeTetra(this->tetramino, actualX, actualY);
    }
    else
    {
        // move the tetramino right
        board.clearTetra(this->tetramino, actualX, actualY);

        this->x++;
        board.placeTetra(this->tetramino, this->x, this->y);
    }
};