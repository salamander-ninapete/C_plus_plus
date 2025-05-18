#include "SnakeView.h"

#include <QApplication>
#include <QHBoxLayout>
#include <QMessageBox>
#include <QVBoxLayout>

SnakeView::SnakeView(s21::SnakeController& controller, QWidget* parent)
    : QMainWindow(parent), controller_(controller), lastActionTime_(0) {
  // Настройка окна

  setWindowTitle("Snake Game");
  resize(800, 600);

  // Создание виджетов
  gameFieldLabel = new QLabel(this);
  scoreLabel = new QLabel("Score: 0", this);
  highScoreLabel = new QLabel("High Score: 0", this);
  levelLabel = new QLabel("Level: 1", this);
  speedLabel = new QLabel("Speed: 5", this);
  statusLabel = new QLabel("", this);
  statusLabeltwo = new QLabel("", this);

  // Размещение виджетов
  QVBoxLayout* rightPanel = new QVBoxLayout();
  rightPanel->addWidget(scoreLabel);
  rightPanel->addWidget(highScoreLabel);
  rightPanel->addWidget(levelLabel);
  rightPanel->addWidget(speedLabel);
  rightPanel->addWidget(statusLabel);
  rightPanel->addWidget(statusLabeltwo);

  QHBoxLayout* mainLayout = new QHBoxLayout();
  mainLayout->addWidget(gameFieldLabel);
  mainLayout->addLayout(rightPanel);

  QWidget* centralWidget = new QWidget(this);
  centralWidget->setLayout(mainLayout);
  setCentralWidget(centralWidget);

  // Настройка таймера
  PreView();
  gameTimer = new QTimer(this);
  connect(gameTimer, &QTimer::timeout, this, &SnakeView::UpdateGame);
  gameTimer->start(30);
  // Инициализация игры
  controller_.GetModel().SetHighScore(ReadHighScore(FILE_FOR_HIGHTSCORE));
  controller_.GetModel().InitGame();
}

SnakeView::~SnakeView() { delete gameTimer; }

void SnakeView::RenderGame() {
  RenderSnakeField();
  RenderRightPanel();
}

void SnakeView::RenderSnakeField() {
  int** field = controller_.GetModel().GetField();
  QPixmap pixmap(F_WIDTH * 30, F_HEIGHT * 30);
  pixmap.fill(Qt::gray);

  QPainter painter(&pixmap);
  painter.setPen(Qt::black);

  for (int y = 0; y < F_HEIGHT; y++) {
    for (int x = 0; x < F_WIDTH; x++) {
      QRect rect(x * 30, y * 30, 30, 30);

      if (field[y][x] == BODY) {
        painter.fillRect(rect, Qt::green);
      } else if (field[y][x] == APPLE) {
        painter.fillRect(rect, Qt::red);
      } else if (field[y][x] == HEAD) {
        painter.fillRect(rect, Qt::yellow);
      } else {
        painter.fillRect(rect, Qt::black);
      }
    }
  }

  gameFieldLabel->setPixmap(pixmap);
}

void SnakeView::RenderRightPanel() {
  scoreLabel->setText(
      QString("Score: %1").arg(controller_.GetModel().GetScore()));
  highScoreLabel->setText(
      QString("High Score: %1").arg(controller_.GetModel().GetHighScore()));
  levelLabel->setText(
      QString("Level: %1").arg(controller_.GetModel().GetLevel()));
  speedLabel->setText(
      QString("Speed: %1").arg(controller_.GetModel().GetSpeed()));

  if (controller_.GetModel().GetAction()) {
    statusLabel->setText("!BO-O-O-OST!");
  } else {
    statusLabel->setText("");
  }
  if (controller_.GetModel().GetPause()) {
    statusLabeltwo->setText("PAUSE");
  } else {
    statusLabeltwo->setText("");
  }
}

void SnakeView::UpdateGame() {
  bool running = controller_.GetModel().GameLogic(&lastActionTime_);
  WriteHighScore(FILE_FOR_HIGHTSCORE);
  RenderGame();
  if (!running) {
    gameTimer->stop();
    ExitView();
  }
}

void SnakeView::ExitView() {
  int score = controller_.GetModel().GetScore();
  if (score == F_HEIGHT * F_WIDTH) {
    RenderWinScreen();
  } else {
    RenderEndScreen(score);
  }
}

void SnakeView::PreView() { RenderStartScreen(); }

void SnakeView::RenderStartScreen() {
  QMessageBox::information(this, "Snake Game",
                           "Добро пожаловать в Snake Game!");
}

void SnakeView::RenderEndScreen(int score) {
  QMessageBox::information(this, "Game Over",
                           QString("Ваш счет: %1").arg(score));
  close();
}

void SnakeView::RenderWinScreen() {
  QMessageBox::information(this, "Победа!", "Вы выиграли!");
}

void SnakeView::keyPressEvent(QKeyEvent* event) {
  controller_.HandleInput(event->key());
}

int SnakeView::ReadHighScore(const std::string& filename) {
  int high_score = 0;
  QFile file(QString::fromStdString(filename));

  if (file.open(QIODevice::ReadOnly | QIODevice::Text)) {
    QTextStream in(&file);
    in >> high_score;
    file.close();
  } else {
    // Если файл не существует, создаем его и записываем начальное значение
    if (file.open(QIODevice::WriteOnly | QIODevice::Text)) {
      QTextStream out(&file);
      out << SCORE_START;
      file.close();
      high_score = SCORE_START;
    } else {
      qWarning() << "Не удалось создать файл:" << file.errorString();
    }
  }

  return high_score;
}

void SnakeView::WriteHighScore(const std::string& filename) {
  if (controller_.GetModel().GetScore() >
      controller_.GetModel().GetHighScore()) {
    QFile file(QString::fromStdString(filename));
    if (file.open(QIODevice::WriteOnly | QIODevice::Text)) {
      QTextStream out(&file);
      out << controller_.GetModel().GetScore();
      file.close();
      controller_.GetModel().SetHighScore(controller_.GetModel().GetScore());
    } else {
      qWarning() << "Не удалось открыть файл для записи:" << file.errorString();
    }
  }
}
