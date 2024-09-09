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
    void updateScore(int deletedLines);
    void updateLevel(int selectLevel);
    // void updateLines(int lines);
    // int getLevel();
    // int getLines();
    WINDOW *getWin();
    int getScore();
};