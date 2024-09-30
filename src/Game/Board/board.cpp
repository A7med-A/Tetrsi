#include "board.hpp"

Board::Board(WINDOW *playwin)

{
    this->playwin = playwin;

    for (int i = 0; i < Board_HEIGHT; i++)
    {
        for (int j = 0; j < Board_WIDTH; j++)
        {
            this->FixedBoard[i][j] = ' ';
        }
    }
    refresh();
}

void Board::draw(WINDOW *test)
{

    for (int i = 0; i < Board_HEIGHT; i++)
    {
        for (int j = 0; j < Board_WIDTH; j++)
        {
            mvwaddch(test, i, j, this->FixedBoard[Board_HEIGHT - 1 - i][j]);
        }
    }
    wrefresh(test);
}

void Board::updateFixedBoardFromWin() // è chiamata quando il tetramino tocca il fondo
{
    wrefresh(this->playwin);
    for (int i = 0; i < Board_HEIGHT; i++)
    {
        for (int j = 0; j < Board_WIDTH; j++)
        {
            this->FixedBoard[Board_HEIGHT - 1 - i][j] = mvwinch(this->playwin, i, j);
        }
    }
    draw(this->playwin);
}

void Board::updateWinFromFixedBoard()
{
    for (int i = 0; i < Board_HEIGHT; i++)
    {
        for (int j = 0; j < Board_WIDTH; j++)
        {
            mvwaddch(this->playwin, i, j, this->FixedBoard[Board_HEIGHT - 1 - i][j]);
        }
    }
    wrefresh(this->playwin);
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
            if (tetra.shape[i][j] != ' ')
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
                clearTetra(tetra, xAttuale, yAttuale); // la differenza tra questa e la rotazione
                if (mvwinch(this->playwin, boardY, boardX) != ' ')
                    return true;
                placeTetra(tetra, xAttuale, yAttuale);
            }
        }
    }
    return false;
}

bool Board::checkRotationCollision(int xAttuale, int yAttuale, Tetra tetra, Tetra rotated)
{
    // Rimuovi temporaneamente il tetramino attuale dalla board per evitare collisioni con se stesso
    clearTetra(tetra, xAttuale, yAttuale);

    for (int i = 0; i < 4; i++)
    {
        for (int j = 0; j < 4; j++)
        {
            if (rotated.shape[i][j] != ' ')
            { // Supponendo che '#' indichi un blocco del tetramino
                int boardX = xAttuale + j;
                int boardY = yAttuale + i;

                // Verifica se il tetramino ruotato è fuori dalla board orizzontalmente
                if (boardX < 0 || boardX >= Board_WIDTH)
                    return true;
                // Verifica se il tetramino ruotato è fuori dalla board verticalmente
                if (boardY < 0 || boardY >= Board_HEIGHT)
                    return true;
                // Verifica collisioni con altri tetramini
                if (mvwinch(this->playwin, boardY, boardX) != ' ')
                {
                    // Se c'è una collisione, riposiziona il tetramino originale e ritorna true
                    placeTetra(tetra, xAttuale, yAttuale);
                    return true;
                }
            }
        }
    }

    // Se non ci sono collisioni, riposiziona il tetramino originale e ritorna false
    placeTetra(tetra, xAttuale, yAttuale);
    return false;
}

void Board::placeTetra(Tetra tetra, int x, int y)
{
    for (int i = 0; i < 4; i++)
    {
        for (int j = 0; j < 4; j++)
        {
            if (tetra.shape[i][j] != ' ')
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
            if (tetra.shape[i][j] != ' ')
            {
                mvwaddch(this->playwin, y + i, x + j, ' '); //////////////AAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAA
            }
        }
    }
    wrefresh(this->playwin);
    // updateBoardFromWin();
}

void Board::resetBoardAndWin()
{
    for (int i = 0; i < Board_HEIGHT; i++)
    {
        for (int j = 0; j < Board_WIDTH; j++)
        {
            this->FixedBoard[i][j] = ' ';
        }
    }
    wclear(this->playwin);
    wrefresh(this->playwin);
}

WINDOW *Board::getWin()
{
    return this->playwin;
}

bool Board::checkGameOver()
{
    for (int i = 0; i < Board_WIDTH; i++)
    {
        if (this->FixedBoard[Board_HEIGHT - 7][i] != ' ') // devo scegliere un qule riga bloccare il gioco
        {
            return true;
        }
    }
    return false;
}

// logica delle linee cancellate

// NOTA IMP:: A[x][y]  x = riga y = colonna
// x=0 vuole dire la riga più in alto
// y=0 vuole dire la colonna più a sinistra
bool Board::isLineComplete(int y)
{
    for (int i = 0; i < Board_WIDTH; i++)
    {
        if (this->FixedBoard[y][i] == ' ')
        {
            return false;
        }
    }
    return true;
}

// funziona correttamente
void Board::removeLine(int y) // y= 0 vuole dire la riga più in basso
{
    for (int ty = y; ty < Board_HEIGHT - 1; ty++) // ty < BoardHi -1  devo decidere a quale riga bloccare la cancellazione(limite del gioco o gameover)
    {
        for (int tx = 0; tx < Board_WIDTH; tx++)
        {
            this->FixedBoard[ty][tx] = this->FixedBoard[ty + 1][tx];
        }
    }
}

// funziona correttamente :)  ma non restituisce il numero corretto di linee cancellate
int Board::clearLines()
{
    int linesCleared = 0;
    for (int i = 0; i < Board_HEIGHT - 1; i++)
    {
        if (isLineComplete(i))
        {
            removeLine(i);
            linesCleared++;
            // Problema risolto con questo decremento
            i--; // dopo aver cancellato una riga devo ricontrollare la riga cancellata (perchè le righe si spostano)
        }
    }
    return linesCleared;
}