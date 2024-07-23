#include <ncurses.h>
#include <iostream>

#include "Game/Board/board.hpp"
#include "Game/Tetramino/tetramino.hpp"
#include "Game/constants.hpp"
#include "Game/Menu/menu.hpp"
#include "Game/Score/score.hpp"

int main()
{
    initscr();
    noecho();

    // le window principali del gioco
    WINDOW *playwin, *scorewin, *menuwin;
    refresh();

    box(stdscr, 0, 0);
    refresh();

    /*
    playwin = newwin(Board_HEIGHT, Board_WIDTH, 10, 10);
    refresh();
    Board board(playwin);
    refresh();
    board.Border();

    ////////////////////////////////////////////////////////// Test che board funzioni bene con la window
    // mvwaddch(playwin, Board_HEIGHT - 1, 0, 'A');
    // wrefresh(playwin);
    // board.updateBoardFromWin();
    // board.board[5][5] = 'B';
    // board.draw();
    //////////////////////////////////////////////////////////

    Tetramino tetramino;
    tetramino.spawnTetramino(board.getWin());
    board.updateBoardFromWin();

    // mvwaddch(playwin, 3, 1, '#');
    wrefresh(playwin);

    // ciclo gioco
    // wtimeout(board.getWin(), 1000);
    // int ch;
    // while (true)
    // {
    //     ch = wgetch(board.getWin());
    //     if (ch == ERR)
    //     {
    //         tetramino.rotate(board);
    //         wrefresh(playwin);
    //     }
    //     else
    //         break;
    // }

    // la funzione wtimeout() permette di aggioranre la finestra ogni tot millisecondi
*/

    ///////////////////////////////////////////// SCORE

    // scorewin = newwin(20, 20, 2, 2);

    // refresh();

    // Score score(scorewin);
    // refresh();

    // score.borderwin();

    // score.draw();

    ////////////////////////////////////////////////////////// MENU

    // menuwin = newwin(50, 50, 2, 2);

    // refresh();

    // Menu menu(menuwin);
    // refresh();
    // menu.DisplayMainMenu();
    // int ch = getch();
    // while (ch != 'q')
    // {
    //     if (ch == 's')
    //     {
    //         wclear(menuwin);
    //         box(menuwin, 0, 0);
    //         mvwprintw(menuwin, 1, 1, "GAME STARTED");
    //         wrefresh(menuwin);
    //     }
    //     ch = getch();
    // }

    ////////////////////////////////////////////////////////// PROVE PRATICHE E GIOCO //////////////////////////////////////////////////////////

    // le 3 fineste: playwin, scorewin, menuwin
    // alcuni parametri che ci servono
    int maxHeigth, maxWidth;
    getmaxyx(stdscr, maxHeigth, maxWidth);

    // inizializzazione gioco
    playwin = newwin(Board_HEIGHT, Board_WIDTH, 10, 10);
    scorewin = newwin(20, 20, 2, 2);
    menuwin = newwin(maxHeigth, maxWidth, 0, 0);
    refresh();

    // inizializzazione delle classi
    Board board(playwin);
    Score score(scorewin);
    Menu menu(menuwin);
    refresh();

    // visualizzo menu principale
    menu.DisplayMainMenu();

    // ciclo principale
    int ch = getch();

    while (ch != 'q')
    {
        if (ch == 's')
        {
            // inizializzo il gioco
            wclear(menuwin);
            box(menuwin, 0, 0);
            mvwprintw(menuwin, 1, 1, "GAME STARTED");
            wrefresh(menuwin);

            // inizializzo il gioco
            board.Border();
            Tetramino tetramino;
            tetramino.spawnTetramino(board.getWin());
            board.updateBoardFromWin();

            // ciclo di gioco
            wtimeout(board.getWin(), Time_Out);
            int ch = wgetch(board.getWin());
            while (ch != 'q')
            {
                if (ch == ERR)
                {
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
                ch = wgetch(board.getWin());
            }
        }
        ch = getch();
    }

    getch();
    endwin();
    return 0;
}