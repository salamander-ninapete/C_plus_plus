#include "../../brick_game/snake/SnakeController.h"
#include "../../brick_game/snake/SnakeModel.h"
#include "SnakeView.h"
namespace s21 {

int SnakeGame() {
  SnakeModel model;
  SnakeController controller(model);
  SnakeView view(controller);
  view.RunGame();
  return 0;
}
}  // namespace s21