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
    mvwprintw(this->scorewin, 1, 1, "Name: %s", this->playerName);
    mvwprintw(this->scorewin, 2, 1, "Score: %d", this->score);
    mvwprintw(this->scorewin, 3, 1, "Level: %d", this->level);
    mvwprintw(this->scorewin, 4, 1, "Lines: %d", this->lines);
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

void Score::sortScoreTable() // bubble sort
{
    for (int i = 0; i < 10; i++)
    {
        for (int j = i + 1; j < 10; j++)
        {
            if (this->scoreTableArray[i].score < this->scoreTableArray[j].score)
            {
                scoreTable temp = this->scoreTableArray[i];
                this->scoreTableArray[i] = this->scoreTableArray[j];
                this->scoreTableArray[j] = temp;
            }
        }
    }
}
// struttura per salvare e ordinare i punteggi
void Score::readScoreFromFileAndSaveInScoreTable(const std::string &filename)
{

    std::ifstream file(filename);
    if (!file.is_open())
    {
        std::cerr << "Error opening file" << std::endl;
        return;
    }
    for (int i = 0; i < 10; i++)
    {
        file >> this->scoreTableArray[i].score;
        file >> this->scoreTableArray[i].name;
    }
    file.close();
}

void Score::saveScoreInFile()
{
    this->sortScoreTable();
    std::ofstream file("scoreTable.txt");
    if (!file.is_open())
    {
        std::cerr << "Error opening file" << std::endl;
        return;
    }
    for (int i = 0; i < 10; i++)
    {
        file << this->scoreTableArray[i].score << " " << this->scoreTableArray[i].name << std::endl;
    }
    file.close();
}

void Score::updateScoreTable()
{

    bool added = false;
    int i = 0;
    while (i < 10 && !added)
    {
        if (this->score > this->scoreTableArray[i].score)
        {
            added = true;
            for (int j = 9; j > i; j--)
            {
                this->scoreTableArray[j] = this->scoreTableArray[j - 1];
            }
            this->scoreTableArray[i].score = this->score;
            strcpy(this->scoreTableArray[i].name, this->playerName);
        }
        i++;
    }
    if (added)
    {
        this->saveScoreInFile();
    }
}

void Score::askLevel()
{

    WINDOW *inputwin = newwin(3, 40, 10, 10);
    box(inputwin, 0, 0);
    mvwprintw(inputwin, 1, 1, "Select Level: from 1 to 5");
    wrefresh(inputwin);
    this->level = getch() - '0';
    wrefresh(inputwin);
    delwin(inputwin);
}

int Score::timeOutBasedOnLevel()
{
    int Time_Out_Input;
    switch (this->level) // scelta tempo in base al livello
    {
    case 1:
        Time_Out_Input = 200;
        break;
    case 2:
        Time_Out_Input = 150;
        break;
    case 3:
        Time_Out_Input = 100;
        break;
    case 4:
        Time_Out_Input = 50;
        break;
    case 5:
        Time_Out_Input = 25;
        break;
    }
    return Time_Out_Input;
}

void Score::askName()
{
    echo();
    WINDOW *inputwin = newwin(3, 40, 10, 10);
    box(inputwin, 0, 0);
    mvwprintw(inputwin, 1, 1, "Enter your name: ");
    wrefresh(inputwin);
    wgetnstr(inputwin, playerName, 20);
    wrefresh(inputwin);
    delwin(inputwin);
    noecho();
}

void Score::resetScore()
{
    this->score = 0;
    this->lines = 0;
    this->level = 1;
    wclear(this->scorewin);
    wrefresh(this->scorewin);
}

WINDOW *Score::getWin()
{
    return this->scorewin;
}

int Score::getScore()
{
    return this->score;
}
