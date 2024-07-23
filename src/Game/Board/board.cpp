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

void Board::updateBoardFromWin() // per ora non utilizzata
{
    for (int i = 0; i < Board_HEIGHT; i++)
    {
        for (int j = 0; j < Board_WIDTH; j++)
        {
            this->board[Board_HEIGHT - 1 - i][j] = mvwinch(this->playwin, i, j);
        }
    }
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
            if (rotated.shape[i][j] == '#')
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

bool Board::checkLine(int line)
{
    for (int i = 0; i < Board_WIDTH; i++)
    {
        if (mvwinch(this->playwin, line, i) == ' ')
        {
            return false;
        }
    }
    return true;
}

bool Board::isLineEmpty(int line)
{
    for (int i = 0; i < Board_WIDTH; i++)
    {
        if (mvwinch(this->playwin, line, i) != ' ')
        {
            return false;
        }
    }
    return true;
}

void Board::moveAllLineDown(int clearedLineY)
{
    // Partendo dalla linea appena sopra quella eliminata, spostiamo tutto verso il basso
    for (int y = clearedLineY; y > 0; y--)
    {
        if (isLineEmpty(y - 1))
        {
            break;
        }
        for (int x = 0; x < Board_WIDTH; x++)
        {
            // Ottieni il carattere dalla linea sopra
            chtype charAbove = mvwinch(this->playwin, y - 1, x);
            // Sposta il carattere nella linea corrente
            mvwaddch(this->playwin, y, x, charAbove);
            wrefresh(this->playwin);
        }
    }

    // Pulisci la linea più in alto dopo lo spostamento
    for (int x = 0; x < Board_WIDTH; x++)
    {
        mvwaddch(this->playwin, 0, x, ' ');
    }

    // Aggiorna la window per riflettere i cambiamenti
    wrefresh(this->playwin);
}

void Board::clearLine(int line)
{
    for (int x = 0; x < Board_WIDTH; x++)
    {
        mvwaddch(this->playwin, line, x, ' ');
    }
    wrefresh(this->playwin);
}
