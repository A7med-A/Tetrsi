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
        this->score += 10;
    }
    else if (deletedLines == 2)
    {
        this->score += 30;
    }
    else if (deletedLines == 3)
    {
        this->score += 45;
    }
    else if (deletedLines == 4)
    {
        this->score += 60;
    }
}

WINDOW *Score::getWin()
{
    return this->scorewin;
}
