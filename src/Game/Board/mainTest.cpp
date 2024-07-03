#include <ncurses.h>
#include <iostream>
#include "board.hpp"

int main()
{
    initscr();
    noecho();
    cbreak();
    curs_set(0);
    keypad(stdscr, TRUE);

    box(stdscr, 0, 0);

    WINDOW *playwin = newwin(Board_HEIGHT, Board_WIDTH, 20, 25);

    Board board(playwin);
    board.Border(); // bordo con una nuova window

    // la posizione effettiva dei bordi della board è -1 rispetto a quella definita in constants.hpp sia in altezza che in larghezza
    mvwaddch(board.getWin(), 19, 99, '#');
    wrefresh(board.getWin());

    board.updateBoardFromWin();
    wrefresh(playwin);

    mvwaddch(board.getWin(), 5, 5, board.board[19][99]);
    wrefresh(board.getWin());

    board.placeTetra(Tetramini[1], 10, 5);

    getch();
    endwin();
    return 0;
}