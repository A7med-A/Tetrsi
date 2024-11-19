
#include <ncurses.h>

#include <cstring>
#include <iostream>

#include "Game/Board/board.hpp"
#include "Game/Menu/menu.hpp"
#include "Game/Score/score.hpp"
#include "Game/Tetramino/tetramino.hpp"
#include "Game/constants.hpp"
#include "game.hpp"

int main() {
  Game game;
  game.run();
  return 0;
}