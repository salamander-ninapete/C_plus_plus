#include "SnakeModel.h"

#include <cstdlib>
#include <ctime>
#include <fstream>

namespace s21 {
SnakeModel::SnakeModel() {
  size_ = LENGHT_START;
  score_ = SCORE_START;
  level_ = T_LVL_START;
  speed_ = SPEED_START;
  high_score_ = SCORE_START;
  pause_ = false;
  cur_state_ = Up;
  moving_ = Up;
  field_ = nullptr;
  action_ = false;
  body_.clear();
  apple_ = {0, 0};
}

SnakeModel::~SnakeModel() {
  for (int i = 0; i < F_HEIGHT; i++) {
    delete[] field_[i];
  }
  delete[] field_;
}

void SnakeModel::InitGame() {
  CreateField();
  SetSnake();
  srand(time(0));
  apple_ = SetApple();
}

void SnakeModel::CreateField() {
  field_ = new int*[F_HEIGHT];
  for (int i = 0; i < F_HEIGHT; i++) {
    field_[i] = new int[F_WIDTH];
    for (int j = 0; j < F_WIDTH; j++) {
      field_[i][j] = FIELD;
    }
  }
}

void SnakeModel::SetSnake() {
  body_.push_back({F_HEIGHT / 2, F_WIDTH / 2});
  body_.push_back({F_HEIGHT / 2 + 1, F_WIDTH / 2});
  body_.push_back({F_HEIGHT / 2 + 2, F_WIDTH / 2});
  body_.push_back({F_HEIGHT / 2 + 3, F_WIDTH / 2});
}

std::pair<int, int> SnakeModel::SetApple() {
  std::pair<int, int> apple;
  int x, y;
  bool collision = false;
  int cycle = 1;
  while (cycle) {
    x = rand() % F_WIDTH;
    y = rand() % F_HEIGHT;
    collision = false;
    for (const auto& segment : body_) {
      if (segment.first == y && segment.second == x) {
        collision = true;
        break;
      }
    }
    if (!collision) cycle = 0;
  }
  apple.first = y;
  apple.second = x;
  return apple;
}

bool SnakeModel::MoveSnake() {
  bool answer = true;
  switch (cur_state_) {
    case Pause:
      pause_ = !pause_;
      cur_state_ = moving_;
      break;
    case Terminate:
      answer = false;
      break;
    case Left:
      if (!pause_) answer = MoveSide(Left);
      break;
    case Right:
      if (!pause_) answer = MoveSide(Right);
      break;
    case Up:
      if (!pause_) answer = MoveSide(Up);
      break;
    case Down:
      if (!pause_) answer = MoveSide(Down);
      break;
    case Action:
      break;
    case Start:
      break;
  }
  return answer;
}

bool SnakeModel::MoveSide(int side) {
  bool answer = true;
  int y = body_[0].first;
  int x = body_[0].second;
  if (side == Left)
    x--;
  else if (side == Up)
    y--;
  else if (side == Right)
    x++;
  else if (side == Down)
    y++;
  if (Collision(y, x) == TRUE) {
    MoveLogic(y, x);
  } else if (Collision(y, x) == STOP) {
  } else {
    answer = false;
  }
  return answer;
}

void SnakeModel::MoveLogic(int y, int x) {
  if (!TookApple(y, x)) body_.pop_back();
  body_.push_front({y, x});
  moving_ = cur_state_;
}

int SnakeModel::Collision(int y, int x) const {
  int answer = TRUE;
  if ((body_[1].first == y) && (body_[1].second == x)) answer = STOP;
  for (int i = 2; i < size_; i++) {
    if ((body_[i].first == y) && (body_[i].second == x)) answer = FALSE;
  }
  if ((y < WALL) || (y > (F_HEIGHT - 1)) || (x < WALL) || (x > (F_WIDTH - 1))) {
    answer = FALSE;
  }
  return answer;
}

bool SnakeModel::TookApple(int y, int x) {
  bool answer = false;
  if ((apple_.first == y) && (apple_.second == x)) {
    answer = true;
    apple_ = SetApple();
    size_++;
    score_++;
  }
  return answer;
}

void SnakeModel::Leveling() {
  int lvl = score_ / COUNT_POINT_FOR_LVL;
  double boost = 0;
  if (action_) boost = 10;
  level_ = lvl;
  if (lvl <= LVL_MAX)
    speed_ = (lvl * SPEED_STEP) + SPEED_START + boost;
  else if (speed_ <= 0)
    speed_ = SPEED_START + boost;
  else if (lvl > LVL_MAX)
    speed_ = SPEED_MAX;
}

int SnakeModel::ReadHighScore(const std::string& filename) {
  FILE* file = fopen(filename.c_str(), "r");
  int high_score = 0;
  if (file) {
    fscanf(file, "%d", &high_score);
    fclose(file);
  } else {
    file = fopen(filename.c_str(), "w");
    fprintf(file, "%d", SCORE_START);
    fclose(file);
  }
  return high_score;
}

void SnakeModel::WriteHighScore(const std::string& filename) {
  if (score_ > high_score_) {
    FILE* file = fopen(filename.c_str(), "w");
    if (file) {
      high_score_ = score_;
      fprintf(file, "%d", score_);
      fclose(file);
    }
  }
}

int SnakeModel::SetScore(int score) { return score_ = score; }

int SnakeModel::SetHighScore(int high_score) {
  return high_score_ = high_score;
}

void SnakeModel::UpdateCurrentState() {
  field_[body_[0].first][body_[0].second] = HEAD;
  for (int i = 1; i < size_; i++) {
    field_[body_[i].first][body_[i].second] = BODY;
  }
  field_[body_[size_].first][body_[size_].second] = FIELD;
  field_[apple_.first][apple_.second] = APPLE;
}

bool SnakeModel::IsActionAllowed(UserAction_s action) const {
  switch (action) {
    case Up:
      return moving_ != Down;
    case Down:
      return moving_ != Up;
    case Left:
      return moving_ != Right;
    case Right:
      return moving_ != Left;
    default:
      return true;
  }
}

void SnakeModel::SetState(UserAction_s action) {
  if (action == Action && action != Start) {
    action_ = !action_;
  } else if (action != Action && action != Start) {
    cur_state_ = action;
  }
}

bool SnakeModel::GameLogic(time_t* lastActionTime) {
  bool answer = size_ < (F_HEIGHT * F_WIDTH);
  clock_t currentTime = clock();
  if (currentTime - *lastActionTime >= CLOCKS_PER_SEC / speed_) {
    answer = MoveSnake();
    *lastActionTime = currentTime;
  }
  Leveling();
  UpdateCurrentState();
  return answer;
}
}  // namespace s21