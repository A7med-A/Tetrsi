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

    scorewin = newwin(20, 20, 2, 2);

    refresh();

    Score score(scorewin);
    refresh();

    score.borderwin();

    score.draw();
    getch();
    endwin();
    return 0;
}