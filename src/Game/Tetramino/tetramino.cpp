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

void Tetramino::spawnTetramino(Board board)
{
    // aggiorno matrice con i tetramini fissi--> nell moveDown
    // board.updateFixedBoardFromWin();             non funziona
    //  spawn tetramino in the middle of the board
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
                mvwaddch(board.getWin(), this->y + i, this->x + j, this->tetramino.shape[i][j]);
            }
        }
    };
    wrefresh(board.getWin());
}

bool Tetramino::checkBottomCollision(Board board)
{
    int actualX = this->x;
    int actualY = this->y;

    if (board.checkCollision(getX(), getY(), actualX, actualY + 1, this->tetramino))
    {
        return true;
    }
    else
    {
        return false;
    }
};

Tetra Tetramino::getTetramino()
{
    return this->tetramino;
};

void Tetramino::rotate(Board board)
{
    int actualX = this->x;
    int actualY = this->y;

    Tetra rotatedTetramino = this->tetramino;
    int numRotatedTetramino;

    if (this->RandomTetramino == 0)
    {
        numRotatedTetramino = 1;
    }
    else if (this->RandomTetramino == 1)
    {
        numRotatedTetramino = 0;
    }

    rotatedTetramino = Tetramini[numRotatedTetramino];

    if (board.checkRotationCollision(actualX, actualY, this->tetramino, rotatedTetramino) || this->RandomTetramino == 2)
    {
    }
    else
    {
        // clear the tetramino
        board.clearTetra(this->tetramino, actualX, actualY);
        this->tetramino = rotatedTetramino;
        this->RandomTetramino = numRotatedTetramino;
        board.placeTetra(this->tetramino, this->x, this->y);
    }
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
        wrefresh(board.getWin());

        // board.updateFixedBoardFromWin(); // aggiorno la board solo i  tetramini fissi nn funziona
        // this->spawnTetramino(board); // lo spawn si fa solo qui
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
