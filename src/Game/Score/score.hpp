#pragma once
#include <ncurses.h>
#include <fstream>
#include <cstring>
#include <iostream>
#include "../constants.hpp"
#include "../Board/board.hpp"
#include "../Tetramino/tetramino.hpp"

class Score
{
public:
    // riguardo lo score
    int score;
    int level;
    int totalLines;
    int lines;
    WINDOW *scorewin;
    // riguardo il salvataggio e il file
    // array di punteggi
    scoreTable scoreTableArray[10];
    char playerName[20];

public:
    Score(WINDOW *scorewin = NULL);
    void borderwin();
    void draw();
    //
    void updateScore(int deletedLines);
    void updateTotalLines(int deletedLines);
    void updateLines(int deletedLines);
    //
    void sortScoreTable();
    void readScoreFromFileAndSaveInScoreTable(const std::string &filename);
    void saveScoreInFile();
    void updateScoreTable();
    //
    void askLevel();
    int timeOutBasedOnLevel();
    void askName();

    void resetScore();

    WINDOW *getWin();
    int getScore();
};