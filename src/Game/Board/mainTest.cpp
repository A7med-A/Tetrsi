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

    WINDOW *playwin = newwin(Board_HEIGHT, Board_WIDTH, 10, 10);

    WINDOW *test = newwin(Board_HEIGHT, Board_WIDTH, 10, 20);

    Board board(playwin);
    board.Border(); // bordo con una nuova window

    // test
    WINDOW *testBorder = newwin(Board_HEIGHT + 2, Board_WIDTH + 2, test->_begy - 1, test->_begx - 1);
    refresh();
    box(testBorder, 0, 0);
    wrefresh(testBorder);

    // la posizione effettiva dei bordi della board è -1 rispetto a quella definita in constants.hpp sia in altezza che in larghezza
    mvwaddch(board.getWin(), 0, 2, '#');                // ok
    mvwaddch(board.getWin(), Board_HEIGHT - 1, 3, '#'); // ok ma non con Board_HEIGHT
    mvwaddch(board.getWin(), 0, Board_WIDTH - 1, '#');  // ok ma non con Board_WIDTH
    mvwaddch(board.getWin(), 0, 0, '#');                // ok

    wrefresh(board.getWin());

    board.updateFixedBoardFromWin();
    board.draw(test);

    // mvwaddch(board.getWin(), 5, 5, board.board[19][99]);
    // wrefresh(board.getWin());

    // board.placeTetra(Tetramini[1], 10, 5);

    getch();
    endwin();
    return 0;
}