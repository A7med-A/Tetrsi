#include <ncurses.h>
#include <iostream>

#include "Game/Board/board.hpp"
#include "Game/Tetramino/tetramino.hpp"
#include "Game/constants.hpp"
#include "Game/Menu/menu.hpp"
#include "Game/Score/score.hpp"

int main()
{
    initscr();
    noecho();
    cbreak();
    curs_set(0);
    keypad(stdscr, TRUE);
    refresh();

    // le window principali del gioco
    WINDOW *playwin, *scorewin, *menuwin;

    playwin = newwin(Board_HEIGHT, Board_WIDTH, 0, 0);
    refresh();
    Board board(playwin);
    board.Border();
    board.draw();
    getch();

    Tetramino tetramino;
    tetramino.spawnTetramino(playwin);
    refresh();

    board.updateBoardFromWin();
    refresh();

    // la funzione wtimeout() permette di aggioranre la finestra ogni tot millisecondi

    getch();
    endwin();
    return 0;
}