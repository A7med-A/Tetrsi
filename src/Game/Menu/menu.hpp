#pragma once
#include <ncurses.h>
#include "../constants.hpp"

class Menu
{
private:
    WINDOW *menuwin;

public:
    Menu(WINDOW *menuwin = NULL);
    void DisplayMainMenu();
};