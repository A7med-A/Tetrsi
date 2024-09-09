#include "score.hpp"

Score::Score(WINDOW *scorewin)
{
    this->scorewin = scorewin;
    this->score = 0;
    this->level = 1;
    this->lines = 0;
}

void Score::borderwin()
{
    box(this->scorewin, 0, 0);
    wrefresh(this->scorewin);
}

void Score::draw()
{
    box(this->scorewin, 0, 0);
    wrefresh(this->scorewin);
    mvwprintw(this->scorewin, 1, 1, "Score: %d", this->score);
    mvwprintw(this->scorewin, 2, 1, "Level: %d", this->level);
    mvwprintw(this->scorewin, 3, 1, "Lines: %d", this->lines);
    wrefresh(this->scorewin);
}

void Score::updateScore(int deletedLines) // dopo deve aggiustare in base al livello scelto
{
    if (deletedLines == 1)
    {
        this->score += (10 * this->level);
    }
    else if (deletedLines == 2)
    {
        this->score += (30 * this->level);
    }
    else if (deletedLines == 3)
    {
        this->score += (45 * this->level);
    }
    else if (deletedLines == 4)
    {
        this->score += (60 * this->level);
    }
}

void Score::updateLevel(int selectLevel)
{
    this->level = selectLevel;
}

WINDOW *Score::getWin()
{
    return this->scorewin;
}

int Score::getScore()
{
    return this->score;
}
