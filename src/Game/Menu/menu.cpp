#include "menu.hpp"

Menu::Menu(WINDOW *menuwin)
{
    this->menuwin = menuwin;
}

void Menu::DisplayMainMenu()
{
    wclear(this->menuwin);
    box(this->menuwin, 0, 0);
    mvwprintw(this->menuwin, 1, 1, "TETRIS");
    mvwprintw(this->menuwin, 2, 1, "Press 's' to start");
    mvwprintw(this->menuwin, 3, 1, "Press 'q' to quit");
    wrefresh(this->menuwin);
}