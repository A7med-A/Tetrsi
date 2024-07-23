#pragma once
#include <ncurses.h>
#define Board_WIDTH 5
#define Board_HEIGHT 30

#define Control_LEFT 'a'
#define Control_RIGHT 'd'
#define Control_DOWN 's'
#define Rotate 'r'
#define Quit 'q'

#define Tetra_NUM 3

#define Time_Out 200
// nel main andò a inizializzare tutte le window che mi servono

// struttura dei tetramini
struct Tetra
{
  char shape[4][4];
};

const Tetra Tetramini[Tetra_NUM] = {

    {{{' ', ' ', ' ', ' '},
      {' ', ' ', ' ', ' '},
      {' ', ' ', ' ', ' '},
      {'#', '#', '#', '#'}}},

    {{{' ', '#', ' ', ' '},
      {' ', '#', ' ', ' '},
      {' ', '#', ' ', ' '},
      {' ', '#', ' ', ' '}}},

    {{{' ', ' ', ' ', ' '},
      {' ', ' ', ' ', ' '},
      {' ', '#', '#', ' '},
      {' ', '#', '#', ' '}}}};

const Tetra TetraminiRuotati[2] = {
    {
        {{' ', '#', ' ', ' '},
         {' ', '#', ' ', ' '},
         {' ', '#', ' ', ' '},
         {' ', '#', ' ', ' '}},

    },
    {
        {{' ', ' ', ' ', ' '},
         {' ', ' ', ' ', ' '},
         {' ', ' ', ' ', ' '},
         {'#', '#', '#', '#'}},
    }};

enum GameState
{
  MENU_MAIN,
  MENU_PAUSE,
  MENU_GAME,
  GAME_OVER,
  GAME_RUNNING,
  GAME_PAUSE
};

enum MenuOption
{
  OPTION_START,
  OPTION_OPTIONS,
  OPTION_EXIT,
  OPTION_BACK
};