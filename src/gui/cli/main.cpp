#include <ncurses.h>

#include "../../brick_game/tetris/tetris.h"
#include "SnakeView.h"

void StartScreen() {
  initscr();
  cbreak();
  noecho();
  curs_set(0);
  keypad(stdscr, TRUE);
  timeout(1);
  clear();
  mvprintw(10, 12, "SNAKE GAME (s)");
  mvprintw(11, 11, "TETRIS GAME (t)");
  mvprintw(12, 13, "QUIT GAME (q)");
  refresh();
}

int main() {
  StartScreen();
  int cycle = TRUE;
  while (cycle) {
    int ch = getch();
    switch (ch) {
      case 's':
        cycle = s21::SnakeGame();
        break;
      case 't':
        cycle = TetrisGame();
        break;
    }
  }
  endwin();
  return 0;
}