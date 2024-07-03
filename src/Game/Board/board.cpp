#include "board.hpp"

Board::Board(WINDOW *playwinClass)

{
    this->playwin = playwinClass;

    for (int i = 0; i < Board_HEIGHT; i++)
    {
        for (int j = 0; j < Board_WIDTH; j++)
        {
            this->board[i][j] = ' ';
        }
    }
    refresh();
}

void Board::draw()
{

    for (int i = 0; i < Board_HEIGHT; i++)
    {
        for (int j = 0; j < Board_WIDTH; j++)
        {
            mvwaddch(this->playwin, i, j, this->board[i][j]);
        }
    }
    wrefresh(this->playwin);
}

void Board::updateBoardFromWin()
{
    for (int i = 0; i < Board_HEIGHT; i++)
    {
        for (int j = 0; j < Board_WIDTH; j++)
        {
            this->board[i][j] = mvwinch(this->playwin, i, j);
        }
    }
    draw();
}

void Board::Border()
{
    WINDOW *borderwin = newwin(Board_HEIGHT + 2, Board_WIDTH + 2, this->playwin->_begy - 1, this->playwin->_begx - 1);
    refresh();
    box(borderwin, 0, 0);
    wrefresh(borderwin);
}

bool Board::isOccupied(int x, int y)
{
    if (this->board[x][y] == ' ')
    {
        return false;
    }
    else
        return true;
}

void Board::placeTetra(Tetra tetra, int x, int y)
{
    for (int i = 0; i < 4; i++)
    {
        for (int j = 0; j < 4; j++)
        {
            if (tetra.shape[i][j] == '#')
            {
                mvwaddch(this->playwin, x + i, y + j, tetra.shape[i][j]);
            }
        }
    }
    updateBoardFromWin();
}

WINDOW *Board::getWin()
{
    return this->playwin;
}
