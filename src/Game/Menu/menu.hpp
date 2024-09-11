#pragma once
#include <fstream>
#include <string>
#include <ncurses.h>
#include "../constants.hpp"

class Menu
{
private:
    WINDOW *menuwin;

public:
    Menu(WINDOW *menuwin = NULL);
    void DisplayMainMenu();

    void DisplayScoreTableMenu(const std::string &filename);
};