#include "SnakeView.h"
namespace s21 {
void SnakeView::RunGame() {
  controller_.GetModel().SetHighScore(
      controller_.GetModel().ReadHighScore(FILE_FOR_HIGHTSCORE));
  controller_.GetModel().InitGame();
  bool running = PreView();
  time_t lastActionTime_ = 0;
  while (running) {
    int ch = getch();
    controller_.HandleInput(ch);
    running = controller_.GetModel().GameLogic(&lastActionTime_);
    controller_.GetModel().WriteHighScore(FILE_FOR_HIGHTSCORE);
    RenderGame();
  }
  ExitView();
}

void SnakeView::ExitView() {
  int score = GGScore();
  if (score == F_HEIGHT * F_WIDTH) {
    RenderWinScreen();
  } else if (score != -1) {
    RenderEndScreen(score);
  } else {
    RenderEndScreenTwo();
  }
  while (getch() != 'q') {
  }
}

bool SnakeView::PreView() {
  RenderStartScreen();
  return StartMenu();
}

bool SnakeView::StartMenu() {
  RenderStartScreen();
  int ans = INF;
  while (ans == INF) {
    int ch = getch();
    ans = controller_.StartMenuCase(ch);
  }
  return ans;
}

SnakeView::SnakeView(SnakeController& controller) : controller_(controller) {
  initscr();
  cbreak();
  noecho();
  curs_set(0);
  keypad(stdscr, TRUE);
  timeout(1);
  start_color();
  init_pair(1, COLOR_RED, COLOR_BLACK);
  init_pair(2, COLOR_GREEN, COLOR_BLACK);
}

SnakeView::~SnakeView() { endwin(); }

void SnakeView::RenderGame() {
  clear();
  RenderSnakeField();
  RenderRightWin();
  refresh();
}

void SnakeView::RenderSnakeField() {
  int** field = GGField();
  for (int y = 0; y < F_HEIGHT; y++) {
    for (int x = 0; x < F_WIDTH; x++) {
      if (field[y][x] == BODY) {
        attron(COLOR_PAIR(2));
        mvprintw(y, x * 3, "(#)");
        attroff(COLOR_PAIR(2));
      } else if (field[y][x] == APPLE) {
        attron(COLOR_PAIR(1));
        mvprintw(y, x * 3, "(`)");
        attroff(COLOR_PAIR(1));
      } else if (field[y][x] == HEAD) {
        attron(COLOR_PAIR(2));
        mvprintw(y, x * 3, "oTo");
        attroff(COLOR_PAIR(2));
      } else {
        mvprintw(y, x * 3, " . ");
      }
    }
  }
}

void SnakeView::RenderRightWin() {
  mvprintw(1, F_WIDTH * 3 + 2, "Score: %d", GGScore());
  mvprintw(2, F_WIDTH * 3 + 2, "High Score: %d", GGHighScore());
  mvprintw(3, F_WIDTH * 3 + 2, "Level: %d", GGLevel());
  mvprintw(4, F_WIDTH * 3 + 2, "Speed: %d", GGSpeed());
  if (GGAction()) mvprintw(5, F_WIDTH * 3 + 2, "!BO-O-O-OST!");
  if (GGPause()) mvprintw(6, F_WIDTH * 3 + 2, "PAUSE");
}

void SnakeView::RenderStartScreen() {
  clear();
  mvprintw(10, 11, "START GAME (s)");
  mvprintw(11, 12, "QUIT GAME (q)");
  refresh();
}

void SnakeView::RenderEndScreen(int score) {
  clear();
  mvprintw(10, 11, "GAME OVER");
  mvprintw(11, 11, "YOUR SCORE: %d", score);
  refresh();
}

void SnakeView::RenderEndScreenTwo() {
  clear();
  mvprintw(10, 11, "SEE YOU LATER");
  refresh();
}

void SnakeView::RenderWinScreen() {
  clear();
  mvprintw(10, 11, "(* * *)  YOU  (* * *) ");
  mvprintw(11, 11, " \\\\|//   WON   \\\\|// ");
  mvprintw(12, 11, "  \\v/    \\!/    \\v/ ");
  refresh();
}
}  // namespace s21