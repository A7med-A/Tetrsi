#include "game.hpp"

Game::Game() { init(); }

Game::~Game() { cleanUp(); }

void Game::init() {
  initscr();
  noecho();
  curs_set(0);
  keypad(stdscr, TRUE);
  box(stdscr, 0, 0);
  refresh();

  int maxHeigth, maxWidth;
  getmaxyx(stdscr, maxHeigth, maxWidth);

  playwin = newwin(Board_HEIGHT, Board_WIDTH, 10, 10);
  scorewin = newwin(20, 20, 2, 60);
  menuwin = newwin(maxHeigth, maxWidth, 0, 0);
  refresh();

  board = new Board(playwin);
  score = new Score(scorewin);
  menu = new Menu(menuwin);

  refresh();

  currentState = MAIN_MENU;
}

void Game::run() {
  while (true) {
    switch (this->currentState) {
      case MAIN_MENU:
        mainMenu();
        break;
      case SCORE_TABLE_MENU:
        scoreTableMenu();
        break;
      case GAME:
        gameLoop();
        break;
      case QUIT:
        return;
      default:
        break;
    }
  }
}

void Game::mainMenu() {
  menu->DisplayMainMenu();
  int ch = getch();
  if (ch == 's') {
    this->currentState = GAME;
  } else if (ch == 't') {
    this->currentState = SCORE_TABLE_MENU;
  } else if (ch == 'q') {
    this->currentState = QUIT;
  }
}

void Game::scoreTableMenu() {
  menu->DisplayScoreTableMenu("scoreTable.txt");
  int ch = getch();
  if (ch == 'b') {
    currentState = MAIN_MENU;
  }
}

void Game::gameLoop() {
  board->resetBoardAndWin();
  score->resetScore();
  wclear(menuwin);
  wrefresh(menuwin);
  score->askLevel();
  int Time_Out_Input = score->timeOutBasedOnLevel();
  score->askName();
  wclear(menuwin);
  box(menuwin, 0, 0);
  mvwprintw(menuwin, 1, 1, "GAME STARTED");
  wrefresh(menuwin);
  score->borderwin();
  score->draw();
  wrefresh(scorewin);
  score->readScoreFromFileAndSaveInScoreTable("scoreTable.txt");
  board->Border();
  Tetramino tetramino;
  tetramino.spawnTetramino(*board);
  wtimeout(board->getWin(), Time_Out_Input);
  int ch = wgetch(board->getWin());
  bool gameOver = false;
  bool CanSpawn = false;
  int lines = 0;

  while (!gameOver && currentState == GAME) {
    lines = board->clearLines();
    if (lines > 0) {
      board->updateWinFromFixedBoard();
      board->draw(playwin);
      score->updateScore(lines);
      score->updateTotalLines(lines);
      score->updateLines(lines);
      score->draw();
      wrefresh(scorewin);
    }
    if (ch == ERR) {
      gameOver = board->checkGameOver();
      if (gameOver) {
        score->updateScoreTable();
        std::cout << "GAME OVER" << std::endl;
        currentState = MAIN_MENU;
      }
      if (CanSpawn) {
        board->updateFixedBoardFromWin();
        tetramino.spawnTetramino(*board);
        CanSpawn = false;
        wrefresh(playwin);
      }
      if (tetramino.checkBottomCollision(*board)) {
        CanSpawn = true;
      }
      tetramino.moveDown(*board);
      wrefresh(playwin);
    } else if (ch == Control_LEFT) {
      tetramino.moveLeft(*board);
      wrefresh(playwin);
    } else if (ch == Control_RIGHT) {
      tetramino.moveRight(*board);
      wrefresh(playwin);
    } else if (ch == Rotate) {
      tetramino.rotate(*board);
      wrefresh(playwin);
    } else if (ch == Control_DOWN) {
      tetramino.moveDown(*board);
      wrefresh(playwin);
    } else if (ch == Quit) {
      score->updateScoreTable();
      currentState = MAIN_MENU;
    }
    ch = wgetch(board->getWin());
  }
}

void Game::cleanUp() {
  delete board;
  delete score;
  delete menu;
  endwin();
}