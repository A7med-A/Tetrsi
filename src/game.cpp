#include "game.hpp"

Game::Game()
{
    this->playwin = newwin(Board_HEIGHT, Board_WIDTH, 10, 10);
    refresh();
    this->board = Board(playwin);
    refresh();
}
void Game::start()
{
}
