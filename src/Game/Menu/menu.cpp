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
    mvwprintw(this->menuwin, 3, 1, "Press 't' to see the score table");
    mvwprintw(this->menuwin, 4, 1, "Press 'q' to quit");
    wrefresh(this->menuwin);
}

void Menu::DisplayScoreTableMenu(const std::string &filename)
{
    wclear(this->menuwin);
    // box(this->menuwin, 0, 0);

    std::ifstream file(filename);
    if (!file.is_open())
    {
        mvwprintw(this->menuwin, 1, 1, "Error opening file");
        wrefresh(this->menuwin);
        return;
    }

    box(this->menuwin, 0, 0);

    std::string line;
    mvwprintw(this->menuwin, 1, 1, "Score Table");
    mvwprintw(this->menuwin, 2, 1, "click 'b' to go back");
    int row = 1;
    while (std::getline(file, line))
    {
        mvwprintw(this->menuwin, row + 2, 2, line.c_str());
        row++;
    }
    file.close();
    wrefresh(this->menuwin);
}