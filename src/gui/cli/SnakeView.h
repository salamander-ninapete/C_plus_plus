#ifndef SNAKEVIEW_H
#define SNAKEVIEW_H

#include <ncurses.h>

#include "../../brick_game/snake/SnakeController.h"
namespace s21 {
class SnakeView {
 public:
  SnakeView(SnakeController& controller);
  ~SnakeView();

  // Отрисовка

  void RunGame();
  void RenderGame();
  void RenderStartScreen();
  void RenderEndScreen(int score);
  void RenderEndScreenTwo();
  void RenderWinScreen();
  void RenderRightWin();

  friend int SnakeGame();

  // GG Get->Get двойные гетеры нужны для повышения читаемости

  int** GGField() { return controller_.GetModel().GetField(); }
  int GGHighScore() { return controller_.GetModel().GetHighScore(); }
  int GGScore() { return controller_.GetModel().GetScore(); }
  int GGLevel() { return controller_.GetModel().GetLevel(); }
  int GGAction() { return controller_.GetModel().GetAction(); }
  int GGPause() { return controller_.GetModel().GetPause(); }
  int GGSpeed() { return controller_.GetModel().GetSpeed(); }

 private:
  SnakeController& controller_;

  void RenderSnakeField();
  bool StartMenu();
  void ExitView();
  bool PreView();
};

int SnakeGame();

}  // namespace s21

#endif  // SNAKEVIEW_H
