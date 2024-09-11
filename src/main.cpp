#include <ncurses.h>
#include <iostream>
#include <cstring>

#include "Game/Board/board.hpp"
#include "Game/Tetramino/tetramino.hpp"
#include "Game/constants.hpp"
#include "Game/Menu/menu.hpp"
#include "Game/Score/score.hpp"

int main()
{
    initscr();
    noecho();
    curs_set(0);
    keypad(stdscr, TRUE);

    // le window principali del gioco
    WINDOW *playwin, *scorewin, *menuwin;
    refresh();

    box(stdscr, 0, 0);
    refresh();
    ////////////////////////////////////////////////////////// PROVE PRATICHE E GIOCO //////////////////////////////////////////////////////////
    // le 3 fineste: playwin, scorewin, menuwin
    // alcuni parametri che ci servono
    int maxHeigth, maxWidth;
    getmaxyx(stdscr, maxHeigth, maxWidth);

    // inizializzazione gioco
    playwin = newwin(Board_HEIGHT, Board_WIDTH, 10, 10);
    WINDOW *test = newwin(Board_HEIGHT, Board_WIDTH, 10, 20);
    scorewin = newwin(20, 20, 2, 60);
    menuwin = newwin(maxHeigth, maxWidth, 0, 0);
    refresh();

    // inizializzazione delle classi
    Board board(playwin);
    Score score(scorewin);
    Menu menu(menuwin);
    refresh();

    // visualizzo menu principale
    menu.DisplayMainMenu();
    wrefresh(menuwin);

    MenuState currentState = MAIN_MENU;
    // ciclo principale
    int ch = getch();

    while (true)
    {
        switch (currentState)
        {
        case MAIN_MENU:
            menu.DisplayMainMenu();
            ch = getch();
            if (ch == 's')
            {
                currentState = GAME;
            }
            else if (ch == 't')
            {
                currentState = SCORE_TABLE_MENU;
            }
            else if (ch == 'q')
            {
                currentState = QUIT;
            }
            break;
        case SCORE_TABLE_MENU:
            menu.DisplayScoreTableMenu("scoreTable.txt");
            ch = getch();
            if (ch == 'b')
            {
                currentState = MAIN_MENU;
            }
            break;

        case GAME:
        {
            // reset board and score
            board.resetBoardAndWin();
            score.resetScore();
            // chiedere livello
            wclear(menuwin);
            wrefresh(menuwin);
            score.askLevel();
            int Time_Out_Input = score.timeOutBasedOnLevel();

            // chiedi nome
            score.askName();

            // inizializzo il gioco
            wclear(menuwin);
            box(menuwin, 0, 0);
            mvwprintw(menuwin, 1, 1, "GAME STARTED");
            wrefresh(menuwin);

            // inizializzo lo score
            score.borderwin();
            score.draw();
            wrefresh(scorewin);
            score.readScoreFromFileAndSaveInScoreTable("scoreTable.txt"); // il file deve essere qui
            // test
            // for (int i = 0; i < 10; i++)
            //{
            //    std::cout << score.scoreTableArray[i].name << " " << score.scoreTableArray[i].score << std::endl;
            //}

            // test
            WINDOW *testBorder = newwin(Board_HEIGHT + 2, Board_WIDTH + 2, test->_begy - 1, test->_begx - 1);
            refresh();
            box(testBorder, 0, 0);
            wrefresh(testBorder);

            // inizializzo il gioco
            board.Border();
            Tetramino tetramino;
            tetramino.spawnTetramino(board);

            // ciclo di gioco
            wtimeout(board.getWin(), Time_Out_Input);
            int ch = wgetch(board.getWin());
            bool gameOver = false;
            bool CanSpawn = false;
            int lines = 0;

            while (!gameOver && currentState == GAME)
            {
                // clear lines
                lines = board.clearLines();
                if (lines > 0)
                {
                    std::cout << "lines: " << lines << std::endl;
                    // update score
                    score.updateScore(lines);
                    score.draw();
                    wrefresh(scorewin);
                }
                if (ch == ERR)
                {
                    //  Game over
                    gameOver = board.checkGameOver();
                    if (gameOver)
                    {
                        score.updateScoreTable();
                        std::cout << "GAME OVER" << std::endl; // il gameover come logica funziona manca decidere in quale riga bloccare il gioco
                        currentState = MAIN_MENU;
                    }
                    if (CanSpawn)
                    {
                        board.updateFixedBoardFromWin();
                        tetramino.spawnTetramino(board);
                        CanSpawn = false;
                        wrefresh(playwin);
                    }
                    if (tetramino.checkBottomCollision(board))
                    {
                        CanSpawn = true;
                    }
                    tetramino.moveDown(board);
                    wrefresh(playwin);
                }
                else if (ch == Control_LEFT)
                {
                    tetramino.moveLeft(board);
                    wrefresh(playwin);
                }
                else if (ch == Control_RIGHT)
                {
                    tetramino.moveRight(board);
                    wrefresh(playwin);
                }
                else if (ch == Rotate)
                {
                    tetramino.rotate(board);
                    wrefresh(playwin);
                }
                else if (ch == Control_DOWN)
                {
                    tetramino.moveDown(board);
                    wrefresh(playwin);
                }
                else if (ch == 'f')
                {
                    // test
                    board.draw(test);
                    wrefresh(test);
                }
                else if (ch == Quit)
                {
                    score.updateScoreTable();
                    currentState = MAIN_MENU;
                }

                ch = wgetch(board.getWin());
            }
            break;
        }
        case QUIT:
            endwin();
            return 0;

        default:
            break;
        }
    }
    // while (ch != 'q')
    // {
    //     if (ch == 's')
    //     {
    //         // chiedere livello
    //         wclear(menuwin);
    //         wrefresh(menuwin);
    //         score.askLevel();
    //         int Time_Out_Input = score.timeOutBasedOnLevel();

    //         // chiedi nome
    //         score.askName();

    //         // inizializzo il gioco
    //         wclear(menuwin);
    //         box(menuwin, 0, 0);
    //         mvwprintw(menuwin, 1, 1, "GAME STARTED");
    //         wrefresh(menuwin);

    //         // inizializzo lo score
    //         score.borderwin();
    //         score.draw();
    //         wrefresh(scorewin);
    //         score.readScoreFromFileAndSaveInScoreTable("scoreTable.txt"); // il file deve essere qui
    //         // test
    //         // for (int i = 0; i < 10; i++)
    //         //{
    //         //    std::cout << score.scoreTableArray[i].name << " " << score.scoreTableArray[i].score << std::endl;
    //         //}

    //         // test
    //         WINDOW *testBorder = newwin(Board_HEIGHT + 2, Board_WIDTH + 2, test->_begy - 1, test->_begx - 1);
    //         refresh();
    //         box(testBorder, 0, 0);
    //         wrefresh(testBorder);

    //         // inizializzo il gioco
    //         board.Border();
    //         Tetramino tetramino;
    //         tetramino.spawnTetramino(board);

    //         // ciclo di gioco
    //         wtimeout(board.getWin(), Time_Out_Input);
    //         int ch = wgetch(board.getWin());
    //         bool gameOver = false;
    //         bool CanSpawn = false;
    //         int lines = 0;

    //         while (ch != Quit && !gameOver)
    //         {
    //             // clear lines
    //             lines = board.clearLines();
    //             if (lines > 0)
    //             {
    //                 std::cout << "lines: " << lines << std::endl;
    //                 // update score
    //                 score.updateScore(lines);
    //                 score.draw();
    //                 wrefresh(scorewin);
    //             }
    //             if (ch == ERR)
    //             {

    //                 //  Game over
    //                 gameOver = board.checkGameOver();
    //                 if (gameOver)
    //                 {
    //                     std::cout << "GAME OVER" << std::endl; // il gameover come logica funziona manca decidere in quale riga bloccare il gioco
    //                 }
    //                 if (CanSpawn)
    //                 {
    //                     board.updateFixedBoardFromWin();
    //                     tetramino.spawnTetramino(board);
    //                     CanSpawn = false;
    //                     wrefresh(playwin);
    //                 }
    //                 if (tetramino.checkBottomCollision(board))
    //                 {
    //                     CanSpawn = true;
    //                 }
    //                 tetramino.moveDown(board);
    //                 wrefresh(playwin);
    //             }
    //             else if (ch == Control_LEFT)
    //             {
    //                 tetramino.moveLeft(board);
    //                 wrefresh(playwin);
    //             }
    //             else if (ch == Control_RIGHT)
    //             {
    //                 tetramino.moveRight(board);
    //                 wrefresh(playwin);
    //             }
    //             else if (ch == Rotate)
    //             {
    //                 tetramino.rotate(board);
    //                 wrefresh(playwin);
    //             }
    //             else if (ch == Control_DOWN)
    //             {
    //                 tetramino.moveDown(board);
    //                 wrefresh(playwin);
    //             }
    //             else if (ch == 'f')
    //             {
    //                 // test

    //                 board.draw(test);
    //                 wrefresh(test);
    //             }
    //             else if (ch == 'c')
    //             {
    //                 // test
    //             }

    //             ch = wgetch(board.getWin());
    //         }
    //     }

    //     if (ch == 't')
    //     {
    //         menu.DisplayScoreTableMenu("scoreTable.txt");
    //     }
    //     // test

    //     score.updateScoreTable();
    //     ch = getch();
    // }

    getch();
    endwin();
    return 0;
}