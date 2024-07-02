#include <ncurses.h>
#include <iostream>
#include "tetramino.hpp"

// https://github.com/shadabk96/tetris-minip/blob/master/datastructure.jpg

// https://github.com/apzsfo/Text-based-Tetris/blob/fa54c46f1b4b1587cf5e3ded6e60e8311c1ce4c8/Game.cpp

int main()
{
    initscr();
    noecho();
    cbreak();
    curs_set(0);
    keypad(stdscr, TRUE);

    Tetramino tet;
    tet.draw(stdscr, 10, 10);
    refresh();
    getch();
    tet.rotate();

    clear();
    tet.draw(stdscr, 10, 10);
    refresh();
    getch();
    endwin();
    return 0;
}