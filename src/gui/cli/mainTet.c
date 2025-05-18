#include "../../brick_game/tetris/tetris.h"

int TetrisGame() {
  GameInfo_t game;
  game.high_score = readHighScore("highscoreTET.txt");
  initializeGame(&game);
  initscr();
  noecho();
  cbreak();
  curs_set(0);
  keypad(stdscr, TRUE);
  start_color();
  init_pair(1, COLOR_GREEN, COLOR_BLACK);
  timeout(1);
  bool running = true;
  showMenu();
  running = handleMenuInput(&game);
  TetFigure figure = placeFigure(&game);
  time_t lastActionTime = 0;
  while (running) {
    userInput(&running, &figure, &game, &lastActionTime);
    timeout(1);
    game = *leveling(&game);
    if (game.score > game.high_score) {
      game.high_score = game.score;
      writeHighScore("highscoreTET.txt", game.high_score);
    }
    renderGame(&game);
  }
  if (game.score == QUIT_IN_MENU)
    showGameOver2();
  else
    showGameOver(&game);
  gameOverCase();
  endwin();
  cleanupGame(&game);
  return 0;
}

bool handleMenuInput(GameInfo_t *game) {
  int ans = INF;
  while (ans == INF) {
    int ch = getch();
    switch (ch) {
      case 's':
        ans = true;
        break;
      case 'q':
        ans = false;
        game->score = QUIT_IN_MENU;
        break;
    }
  }
  return ans;
}

int gameOverCase() {
  int ans = INF;
  while (ans == INF) {
    int ch = getch();
    switch (ch) {
      case 'q':
        ans = true;
        break;
    }
  }
  return ans;
}

int userInput(bool *running, TetFigure *figure, GameInfo_t *game,
              time_t *lastActionTime) {
  UserAction_t action = T_Start;
  int ch = getch();
  if (*running) {
    clock_t currentTime = clock();
    if (currentTime - *lastActionTime >= CLOCKS_PER_SEC / game->speed) {
      action = T_Up;
      *running = moveFigure(action, figure, game);
      *lastActionTime = currentTime;
    }
    switch (ch) {
      case 'q':
        *running = false;
        action = T_Terminate;
        *running = moveFigure(action, figure, game);
        break;
      case KEY_LEFT:
        action = T_Left;
        moveFigure(action, figure, game);
        break;
      case KEY_RIGHT:
        action = T_Right;
        moveFigure(action, figure, game);
        break;
      case KEY_DOWN:
        action = T_Down;
        moveFigure(action, figure, game);
        break;
      case ' ':
        action = T_Action;
        moveFigure(action, figure, game);
        break;
      case 'p':
        action = T_Pause;
        moveFigure(action, figure, game);
        break;
      case 's':
        action = T_Start;
        *running = moveFigure(action, figure, game);
        break;
    }
  }
  return *running;
}
