#ifndef SNAKEMODEL_H
#define SNAKEMODEL_H

#include <deque>
#include <string>
#include <utility>

#define F_WIDTH 10
#define F_HEIGHT 20
#define WALL 0
#define SCORE_START 0
#define T_LVL_START 0
#define LVL_MAX 10
#define SPEED_STEP 2
#define SPEED_START 5
#define SPEED_MAX 25
#define COUNT_POINT_FOR_LVL 5
#define LENGHT_START 4
#define STOP 2
#define FILE_FOR_HIGHTSCORE "highScoreSnake.txt"
#define QUIT_IN_MENU -1
#define INF -1
#define TRUE 1
#define FALSE 0

typedef enum {
  FIELD,  // Поле
  BODY,   // Тело
  APPLE,  // Яблоко
  HEAD,   // Голова
} FieldPart;

typedef enum {
  Start,      // угу <<(O)v(O)>>
  Pause,      // Пауза / снять с паузы
  Terminate,  // Выход
  Left,       // Движение в лево
  Right,      // Движение в право
  Up,         // Движение вверх
  Down,       // Движение вниз
  Action      // Ускорение
} UserAction_s;

namespace s21 {
class SnakeModel {
 public:
  SnakeModel();
  ~SnakeModel();

  // Геттеры
  int** GetField() const { return field_; }
  std::pair<int, int> GetApple() const { return apple_; }
  std::deque<std::pair<int, int>> GetBody() const { return body_; }
  int GetScore() const { return score_; }
  int GetLevel() const { return level_; }
  double GetSpeed() const { return speed_; }
  bool GetPause() const { return pause_; }
  int GetHighScore() const { return high_score_; }
  int GetSize() const { return size_; }
  UserAction_s GetCurState() const { return cur_state_; }
  bool GetAction() const { return action_; }

  // Инициализация игры
  void InitGame();

  // Логика игры
  bool GameLogic(time_t* lastActionTime);
  bool MoveSnake();
  void Leveling();
  std::pair<int, int> SetApple();
  bool IsActionAllowed(UserAction_s action) const;
  void SetState(UserAction_s action);
  void WriteHighScore(const std::string& filename);
  int SetScore(int score);
  int SetHighScore(int high_score);
  int ReadHighScore(const std::string& filename);

  // из-за тестов

  void CreateField();
  bool TookApple(int y, int x);
  void SetSnake();
  void UpdateCurrentState();

 private:
  // Внутренние методы
  bool MoveSide(int side);
  void MoveLogic(int y, int x);
  int Collision(int y, int x) const;

  // Данные игры
  int size_;
  int** field_;
  std::pair<int, int> apple_;
  std::deque<std::pair<int, int>> body_;
  int score_;
  int high_score_;
  int level_;
  double speed_;
  bool pause_;
  UserAction_s cur_state_;
  UserAction_s moving_;
  bool action_;
};
}  // namespace s21
#endif  // SNAKEMODEL_H