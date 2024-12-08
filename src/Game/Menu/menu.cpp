#include "menu.hpp"

Menu::Menu(WINDOW *menuwin) { this->menuwin = menuwin; }

void Menu::DisplayMainMenu() {
  wclear(this->menuwin);
  box(this->menuwin, 0, 0);
  int width = getmaxx(this->menuwin);
  int hight = getmaxy(this->menuwin);
  mvwprintw(this->menuwin, (hight / 2) - 7, (width / 2) - 5,  "TETRIS");
  mvwprintw(this->menuwin, (hight / 2) - 3, (width / 2) - 13, "Press 's' to start");
  mvwprintw(this->menuwin, (hight / 2) - 1, (width / 2) - 13, "Press 't' for the score table");
  mvwprintw(this->menuwin, (hight / 2) + 1, (width / 2) - 13, "Press 'q' to quit");
  wrefresh(this->menuwin);

}

void Menu::DisplayScoreTableMenu(const std::string &filename) {
  wclear(this->menuwin);
  // box(this->menuwin, 0, 0);

  std::ifstream file(filename);
  if (!file.is_open()) {
    mvwprintw(this->menuwin, 1, 1, "Error opening file");
    wrefresh(this->menuwin);
    return;
  }

  box(this->menuwin, 0, 0);

  int width = getmaxx(this->menuwin);
  int hight = getmaxy(this->menuwin);

  std::string line;
  mvwprintw(this->menuwin, 3, (width / 2) - 5, "SCORE TABLE");
  mvwprintw(this->menuwin, (hight - 13), (width / 2) - 9, "click 'b' to go back");
  int row = 1;
  while (std::getline(file, line)) {
    mvwprintw(this->menuwin, row + 7, (width / 2) - 4, line.c_str());
    row += 3;
  }
  file.close();
  wrefresh(this->menuwin);
}