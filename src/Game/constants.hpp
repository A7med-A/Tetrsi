#include <ncurses.h>
#define Board_WIDTH 100
#define Board_HEIGHT 20

#define Control_LEFT 'a'
#define Control_RIGHT 'd'
#define Control_DOWN 's'
#define Rotate 'r'
#define Quit 'q'

#define Tetra_NUM 3

#define Time_Out 100
// nel main andò a inizializzare tutte le window che mi servono

// struttura dei tetramini
struct Tetra
{
  char shape[4][4];
};

const Tetra Tetramini[Tetra_NUM] = {

    {{{' ', ' ', ' ', ' '},
      {'#', '#', '#', '#'},
      {' ', ' ', ' ', ' '},
      {' ', ' ', ' ', ' '}}},

    {{{' ', '#', ' ', ' '},
      {' ', '#', ' ', ' '},
      {' ', '#', ' ', ' '},
      {' ', '#', ' ', ' '}}},

    {{{' ', ' ', ' ', ' '},
      {' ', '#', '#', ' '},
      {' ', '#', '#', ' '},
      {' ', ' ', ' ', ' '}}}};

const Tetra TetraminiRuotati[2] = {
    {
        {{' ', '#', ' ', ' '},
         {' ', '#', ' ', ' '},
         {' ', '#', ' ', ' '},
         {' ', '#', ' ', ' '}},

    },
    {
        {{' ', ' ', ' ', ' '},
         {'#', '#', '#', '#'},
         {' ', ' ', ' ', ' '},
         {' ', ' ', ' ', ' '}},
    }};