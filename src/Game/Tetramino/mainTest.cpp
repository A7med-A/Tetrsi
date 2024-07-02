#include <ncurses.h>
#include <iostream>
#include "tetramino.hpp"

int main()
{
    initscr();
    noecho();
    cbreak();
    curs_set(0);
    keypad(stdscr, TRUE);

    Tetramino tetramino;
    Tetra tetra = Tetramini[0];
    tetramino.draw(stdscr, tetra, 10, 10);
    refresh();
    getch();
    endwin();
    return 0;
}