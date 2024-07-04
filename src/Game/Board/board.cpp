#include "board.hpp"

Board::Board(WINDOW *playwin)

{
    this->playwin = playwin;

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
            mvwaddch(this->playwin, i, j, this->board[Board_HEIGHT - 1 - i][j]);
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
            this->board[Board_HEIGHT - 1 - i][j] = mvwinch(this->playwin, i, j);
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

bool Board::checkCollision(int xAttuale, int yAttuale, int xVoluto, int yVoluto, Tetra tetra)
{
    for (int i = 0; i < 4; i++)
    {
        for (int j = 0; j < 4; j++)
        {
            if (tetra.shape[i][j] == '#')
            {
                // Coordinate effettive sulla board
                int boardX = xVoluto + j; //////////////AAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAA
                int boardY = yVoluto + i;

                // Controllo se il tetramino è fuori dalla board orizzontalmente
                if (boardX < 0 || boardX >= Board_WIDTH)
                    return true;
                // Controllo se il tetramino è fuori dalla board verticalmente
                if (boardY < 0 || boardY >= Board_HEIGHT)
                    return true;
                // verifica collisioni con altri tetramini
                clearTetra(tetra, xAttuale, yAttuale);
                if (mvwinch(this->playwin, boardY, boardX) != ' ')
                    return true;
                placeTetra(tetra, xAttuale, yAttuale);
            }
        }
    }
    return false;
}

void Board::placeTetra(Tetra tetra, int x, int y)
{
    for (int i = 0; i < 4; i++)
    {
        for (int j = 0; j < 4; j++)
        {
            if (tetra.shape[i][j] == '#')
            {
                mvwaddch(this->playwin, y + i, x + j, tetra.shape[i][j]);
            }
        }
    }
    wrefresh(this->playwin);
    // updateBoardFromWin();
}

void Board::clearTetra(Tetra tetra, int x, int y)
{
    for (int i = 0; i < 4; i++)
    {
        for (int j = 0; j < 4; j++)
        {
            if (tetra.shape[i][j] == '#')
            {
                mvwaddch(this->playwin, y + i, x + j, ' '); //////////////AAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAA
            }
        }
    }
    wrefresh(this->playwin);
    // updateBoardFromWin();
}

WINDOW *Board::getWin()
{
    return this->playwin;
}
