#ifndef SNAKECONTROLLER_H
#define SNAKECONTROLLER_H
#include "SnakeModel.h"

namespace s21 {
class SnakeController {
 public:
  SnakeController(SnakeModel& model);
  void HandleInput(int ch);
  UserAction_s ConvertInputToAction(int button) const;
  int StartMenuCase(int ch);

  SnakeModel& GetModel() { return model_; }

 private:
  SnakeModel& model_;

  // Внутренние методы
};
}  // namespace s21
#endif  // SNAKECONTROLLER_H
