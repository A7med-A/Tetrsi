#pragma once
#include <ncurses.h>

#include <iostream>

#include "Game/Board/board.hpp"
#include "Game/Menu/menu.hpp"
#include "Game/Score/score.hpp"
#include "Game/Tetramino/tetramino.hpp"
#include "Game/constants.hpp"

// è la classe che gestisce tutti i piccoli aspetti del gioco
// dalla inizializzazione delle finestre alla gestione del gioco
class Game {
 public:
  Game();
  ~Game();
  void run();

 protected:
  WINDOW *playwin, *scorewin, *menuwin;
  Board *board;
  Score *score;
  Menu *menu;
  MenuState currentState;

  void init();
  void mainMenu();
  void scoreTableMenu();
  void gameLoop();
  void cleanUp();
};