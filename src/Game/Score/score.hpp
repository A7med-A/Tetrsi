#pragma once
#include <ncurses.h>
#include "../constants.hpp"
#include "../Board/board.hpp"
#include "../Tetramino/tetramino.hpp"

class Score
{
public:
    int score;
    int level;
    int lines;
    WINDOW *scorewin;

public:
    Score(WINDOW *scorewin = NULL);
    void borderwin();
    void draw();
    // void updateScore(int lines);
    // void updateLevel();
    // void updateLines(int lines);
    // int getScore();
    // int getLevel();
    // int getLines();
    WINDOW *getWin();
};