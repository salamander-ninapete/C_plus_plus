#include "test.h"
TEST(SnakeModelTest, ConstructorAndGetters) {
  s21::SnakeModel model;
  model.CreateField();

  EXPECT_EQ(model.GetSize(), LENGHT_START);
  EXPECT_EQ(model.GetScore(), SCORE_START);
  EXPECT_EQ(model.GetLevel(), T_LVL_START);
  EXPECT_EQ(model.GetSpeed(), SPEED_START);
  EXPECT_FALSE(model.GetPause());
  EXPECT_EQ(model.GetCurState(), Up);
  EXPECT_FALSE(model.GetAction());
}
TEST(SnakeModelTest, InitGame) {
  s21::SnakeModel model;
  model.InitGame();

  EXPECT_NE(model.GetField(), nullptr);
  EXPECT_EQ(model.GetBody().size(), LENGHT_START);
  EXPECT_NE(model.GetApple(), std::make_pair(-1, -1));
}

TEST(SnakeModelTest, MoveSnake) {
  s21::SnakeModel model;
  model.InitGame();
  model.SetState(Right);

  EXPECT_TRUE(model.MoveSnake());

  model.SetState(Down);

  EXPECT_TRUE(model.MoveSnake());
}

TEST(SnakeModelTest, SetAndGetScore) {
  s21::SnakeModel model;
  model.CreateField();
  model.SetScore(100);

  EXPECT_EQ(model.GetScore(), 100);
}

TEST(SnakeModelTest, CollisionHandling) {
  s21::SnakeModel model;
  model.InitGame();
  model.SetState(Left);

  EXPECT_TRUE(model.MoveSnake());

  model.SetState(Up);

  EXPECT_TRUE(model.MoveSnake());
}

TEST(SnakeModelTest, SetAndGetHighScore) {
  s21::SnakeModel model;
  model.CreateField();
  model.SetHighScore(200);

  EXPECT_EQ(model.GetHighScore(), 200);
}

TEST(SnakeControllerTest, HandleInput) {
  s21::SnakeModel model;
  s21::SnakeController controller(model);
  model.CreateField();
  controller.HandleInput('w');

  EXPECT_EQ(model.GetCurState(), Up);
}

TEST(SnakeControllerTest, ConvertInputToAction) {
  s21::SnakeModel model;
  model.CreateField();
  s21::SnakeController controller(model);

  EXPECT_EQ(controller.ConvertInputToAction('w'), Up);
  EXPECT_EQ(controller.ConvertInputToAction('a'), Left);
  EXPECT_EQ(controller.ConvertInputToAction('s'), Down);
  EXPECT_EQ(controller.ConvertInputToAction('d'), Right);
  EXPECT_EQ(controller.ConvertInputToAction('p'), Pause);
  EXPECT_EQ(controller.ConvertInputToAction(' '), Action);
  EXPECT_EQ(controller.ConvertInputToAction('q'), Terminate);
}

TEST(SnakeControllerTest, StartMenuCase) {
  s21::SnakeModel model;
  model.CreateField();
  s21::SnakeController controller(model);

  EXPECT_EQ(controller.StartMenuCase('s'), true);
  EXPECT_EQ(controller.StartMenuCase('q'), false);
}

TEST(SnakeModelTest, MoveSnakePause) {
  s21::SnakeModel model;
  model.CreateField();
  model.SetState(Pause);

  EXPECT_TRUE(model.MoveSnake());
  EXPECT_TRUE(model.GetPause());
}

TEST(SnakeModelTest, MoveSnakeTerminate) {
  s21::SnakeModel model;
  model.CreateField();
  model.SetState(Terminate);

  EXPECT_FALSE(model.MoveSnake());
}

TEST(SnakeModelTest, MoveSnakeAction) {
  s21::SnakeModel model;
  model.CreateField();
  model.SetState(Action);

  EXPECT_FALSE(model.MoveSnake());
  EXPECT_FALSE(model.GetPause());
}

TEST(SnakeModelTest, MoveSnakeStart) {
  s21::SnakeModel model;
  model.CreateField();
  model.SetState(Start);

  EXPECT_FALSE(model.MoveSnake());
  EXPECT_FALSE(model.GetPause());
}

TEST(SnakeModelTest, TookAppleWhenEaten) {
  s21::SnakeModel model;
  model.InitGame();
  std::pair<int, int> apple_pos = model.GetApple();
  bool result = model.TookApple(apple_pos.first, apple_pos.second);

  EXPECT_TRUE(result);

  std::pair<int, int> new_apple_pos = model.GetApple();

  EXPECT_NE(new_apple_pos, apple_pos);
  EXPECT_EQ(model.GetSize(), LENGHT_START + 1);
  EXPECT_EQ(model.GetScore(), SCORE_START + 1);
}

TEST(SnakeModelTest, LevelingWithAllConditions) {
  s21::SnakeModel model;
  model.CreateField();
  model.SetScore(COUNT_POINT_FOR_LVL * 2);
  model.SetState(Action);
  model.Leveling();

  EXPECT_EQ(model.GetLevel(), 2);

  double expected_speed = (2 * SPEED_STEP) + SPEED_START + 10;

  EXPECT_EQ(model.GetSpeed(), expected_speed);

  model.SetScore(COUNT_POINT_FOR_LVL * (LVL_MAX + 1));
  model.Leveling();

  EXPECT_EQ(model.GetSpeed(), SPEED_MAX);

  model.SetScore(COUNT_POINT_FOR_LVL * (LVL_MAX + 1));
  model.Leveling();

  EXPECT_EQ(model.GetSpeed(), SPEED_START + 20);
}

TEST(SnakeModelTest, ReadHighScoreAllScenarios) {
  s21::SnakeModel model;
  model.CreateField();
  std::string filename = "test_highscore.txt";

  {
    std::ofstream outfile(filename);
    outfile << "150";
    outfile.close();
    int high_score = model.ReadHighScore(filename);

    EXPECT_EQ(high_score, 150);

    std::remove(filename.c_str());
  }

  {
    std::remove(filename.c_str());
    int high_score = model.ReadHighScore(filename);

    EXPECT_EQ(high_score, SCORE_START);

    std::ifstream infile(filename);
    int file_score = 0;
    infile >> file_score;
    infile.close();

    EXPECT_EQ(file_score, SCORE_START);

    std::remove(filename.c_str());
  }

  {
    std::ofstream outfile(filename);
    outfile.close();
    int high_score = model.ReadHighScore(filename);

    EXPECT_EQ(high_score, SCORE_START);

    std::ifstream infile(filename);
    int file_score = 0;
    infile >> file_score;
    infile.close();

    EXPECT_EQ(file_score, SCORE_START);

    std::remove(filename.c_str());
  }
}

TEST(SnakeModelTest, WriteHighScoreAllScenarios) {
  s21::SnakeModel model;
  model.CreateField();
  std::string filename = "test_highscore.txt";

  {
    model.SetScore(100);
    model.SetHighScore(50);
    model.WriteHighScore(filename);

    EXPECT_EQ(model.GetHighScore(), 100);

    std::ifstream infile(filename);
    int file_score;
    infile >> file_score;
    infile.close();

    EXPECT_EQ(file_score, 100);

    std::remove(filename.c_str());
  }

  {
    model.SetScore(50);
    model.SetHighScore(100);
    std::ofstream outfile(filename);
    outfile << model.GetHighScore();
    outfile.close();
    model.WriteHighScore(filename);

    EXPECT_EQ(model.GetHighScore(), 100);

    std::ifstream infile(filename);
    int file_score;
    infile >> file_score;
    infile.close();

    EXPECT_EQ(file_score, 100);

    std::remove(filename.c_str());
  }

  {
    model.SetScore(200);
    model.SetHighScore(100);
    std::ofstream outfile(filename);
    outfile << model.GetHighScore();
    outfile.close();
    std::filesystem::permissions(filename, std::filesystem::perms::owner_read);
    model.WriteHighScore(filename);

    EXPECT_EQ(model.GetHighScore(), 100);

    std::filesystem::permissions(filename, std::filesystem::perms::owner_write);
    std::remove(filename.c_str());
  }
}

TEST(SnakeModelTest, UpdateCurrentStateTest) {
  s21::SnakeModel model;
  model.CreateField();
  model.SetSnake();
  model.SetApple();

  model.UpdateCurrentState();

  int** field = model.GetField();
  EXPECT_EQ(field[model.GetBody()[0].first][model.GetBody()[0].second], HEAD);
  EXPECT_EQ(field[model.GetApple().first][model.GetApple().second], APPLE);

  for (size_t i = 1; i < model.GetBody().size(); ++i) {
    EXPECT_EQ(field[model.GetBody()[i].first][model.GetBody()[i].second], BODY);
  }
}

TEST(SnakeModelTest, IsActionAllowedTest) {
  s21::SnakeModel model;
  model.CreateField();

  EXPECT_TRUE(model.IsActionAllowed(Left));
  EXPECT_TRUE(model.IsActionAllowed(Up));
  EXPECT_FALSE(model.IsActionAllowed(Down));
  EXPECT_TRUE(model.IsActionAllowed(Start));
}

TEST(SnakeModelTest, GameLogicTest) {
  s21::SnakeModel model;
  time_t lastActionTime = clock();

  model.InitGame();
  bool result = model.GameLogic(&lastActionTime);

  EXPECT_TRUE(result);
  EXPECT_GE(clock(), lastActionTime);

  int** field = model.GetField();
  EXPECT_EQ(field[model.GetBody()[0].first][model.GetBody()[0].second], HEAD);
}

int main(int argc, char** argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}