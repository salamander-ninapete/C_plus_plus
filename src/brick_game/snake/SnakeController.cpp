
#include "SnakeController.h"

namespace s21 {
SnakeController::SnakeController(SnakeModel& model) : model_(model) {}

void SnakeController::HandleInput(int ch) {
  UserAction_s action = ConvertInputToAction(ch);
  if (model_.IsActionAllowed(action)) {
    model_.SetState(action);
  }
}

UserAction_s SnakeController::ConvertInputToAction(int button) const {
  switch (button) {
    case 'q':
    case 'Q':
      return Terminate;
    case 'w':
    case 'W':
      return Up;
    case 'a':
    case 'A':
      return Left;
    case 's':
    case 'S':
      return Down;
    case 'd':
    case 'D':
      return Right;
    case 'p':
    case 'P':
      return Pause;
    case ' ':
      return Action;
    default:
      return Start;
  }
}

int SnakeController::StartMenuCase(int ch) {
  int ans = INF;
  switch (ch) {
    case 's':
      ans = true;
      break;
    case 'q':
      ans = false;
      model_.SetScore(QUIT_IN_MENU);
      break;
  }
  return ans;
}
}  // namespace s21