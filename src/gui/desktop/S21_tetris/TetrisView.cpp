#include "TetrisView.h"

#include <QApplication>
#include <QMessageBox>
#include <QPainter>

TetrisView::TetrisView(QWidget *parent) : QWidget(parent), running(true) {
  setFixedSize(WIDTH * 20 + 200,
               (HEIGHT + SDWIG) * 20 + 20);  // +200 для правой панели
  showMenu();
  game.high_score = ReadHighScore(TET_FILE_FOR_HIGHTSCORE);
  initializeGame(&game);
  figure = placeFigure(&game);

  timer = new QTimer(this);
  connect(timer, &QTimer::timeout, this, &TetrisView::updateGame);
  int interval = 10000 / game.speed;
  if (interval <= 0) interval = 1000;
  timer->start(interval);
}

TetrisView::~TetrisView() {
  cleanupGame(&game);  // Очистка памяти
  delete timer;        // Удаление таймера
}

void TetrisView::paintEvent(QPaintEvent *event) {
  QPainter painter(this);
  renderGame();  // Отрисовка игры
}

void TetrisView::keyPressEvent(QKeyEvent *event) {
  if (!running) return;  // Если игра не запущена, игнорируем ввод

  UserAction_t action = T_Start;

  switch (event->key()) {
    case Qt::Key_Left:
      action = T_Left;
      break;
    case Qt::Key_Right:
      action = T_Right;
      break;
    case Qt::Key_Down:
      action = T_Down;
      break;
    case Qt::Key_Space:
      action = T_Action;
      break;
    case Qt::Key_P:
      action = T_Pause;
      break;
    case Qt::Key_Q:
      action = T_Terminate;
      running = false;
      break;
    case Qt::Key_S:
      action = T_Start;
      close();
      break;
    default:
      return;  // Игнорируем другие клавиши
  }

  // Обработка действия
  running = moveFigure(action, &figure, &game);

  // Если игра завершена, показываем экран завершения
  if (!running) {
    if (game.score == QUIT_IN_MENU) {
      showGameOver2();
    } else {
      showGameOver();
    }
    gameOverCase();
  }

  update();  // Обновляем отрисовку
}

void TetrisView::updateGame() {
  if (!game.pause && running) {
    bool success =
        moveFigure(T_Up, &figure, &game);  // Автоматическое падение фигуры
    WriteHighScore(TET_FILE_FOR_HIGHTSCORE);
    game = *leveling(&game);
    int interval = 10000 / game.speed;
    timer->start(interval);
    if (!success) {
      // Фигура достигла дна
      placeFigureOnField(&game, &figure);  // Закрепляем фигуру на поле
      figure = placeFigure(&game);  // Создаем новую фигуру
      if (!checkCollision(game, figure, 0, 1)) {
        // Игра окончена

        running = false;
        timer->stop();
        showGameOver();
      }
    }
    update();  // Обновление отрисовки
  }
}

void TetrisView::renderGame() {
  QPainter painter(this);

  // Отрисовка игрового поля
  for (int y = 1; y < HEIGHT + SDWIG; y++) {
    for (int x = 0; x < WIDTH; x++) {
      if (game.field[y][x]) {
        painter.fillRect(x * 20 + 20, y * 20, 20, 20,
                         Qt::darkGreen);  // Заливаем клетку, если она занята
      } else {
        painter.fillRect(x * 20 + 20, y * 20, 20, 20,
                         Qt::white);  // Пустая клетка
      }
    }
  }

  // Отрисовка правой панели
  int panelX = WIDTH * 20 + 20;  // Начало правой панели
  int panelY = 20;               // Отступ сверху

  // Отрисовка счета, уровня и паузы
  painter.drawText(panelX + 20, panelY + 20,
                   "Score: " + QString::number(game.score));
  painter.drawText(panelX + 20, panelY + 40,
                   "High Score: " + QString::number(game.high_score));
  painter.drawText(panelX + 20, panelY + 60,
                   "Level: " + QString::number(game.level));

  if (game.pause) {
    painter.drawText(panelX + 20, panelY + 80, "PAUSED");
  }

  // Отрисовка следующей фигуры
  renderNextFigure(&painter);
}

void TetrisView::renderNextFigure(QPainter *painter) {
  int x = WIDTH * 20 + 20;  // Начало правой панели
  int y = 100;  // Отступ сверху для следующей фигуры
  int blockSize = 20;  // Размер одного блока

  switch (game.next_fig) {
    case 0:  // I-фигура
      painter->fillRect(x + 20, y + blockSize, blockSize * 4, blockSize,
                        Qt::darkGreen);
      break;
    case 1:  // O-фигура
      painter->fillRect(x + 20 + blockSize, y, blockSize * 2, blockSize * 2,
                        Qt::darkGreen);
      break;
    case 2:  // T-фигура
      painter->fillRect(x + 20, y + blockSize, blockSize * 3, blockSize,
                        Qt::darkGreen);  // Горизонтальная часть
      painter->fillRect(x + 20 + blockSize, y, blockSize, blockSize,
                        Qt::darkGreen);  // Вертикальная часть
      break;
    case 3:  // S-фигура
      painter->fillRect(x + 20 + blockSize, y, blockSize * 2, blockSize,
                        Qt::darkGreen);  // Верхняя часть
      painter->fillRect(x + 20, y + blockSize, blockSize * 2, blockSize,
                        Qt::darkGreen);  // Нижняя часть
      break;
    case 4:  // Z-фигура
      painter->fillRect(x + 20, y, blockSize * 2, blockSize,
                        Qt::darkGreen);  // Верхняя часть
      painter->fillRect(x + 20 + blockSize, y + blockSize, blockSize * 2,
                        blockSize,
                        Qt::darkGreen);  // Нижняя часть
      break;
    case 5:  // J-фигура

      painter->fillRect(x + 20 + blockSize, y, blockSize, blockSize * 3,
                        Qt::darkGreen);  // Вертикальная часть
      painter->fillRect(x + 20, y + blockSize * 2, blockSize * 2, blockSize,
                        Qt::darkGreen);  // Нижняя часть

      break;
    case 6:  // L-фигура
      painter->fillRect(x + 20, y, blockSize, blockSize * 3,
                        Qt::darkGreen);  // Вертикальная часть
      painter->fillRect(x + 20 + blockSize, y + blockSize * 2, blockSize,
                        blockSize,
                        Qt::darkGreen);  // Нижняя часть
      break;
  }
}
void TetrisView::showMenu() {
  QMessageBox::information(this, "Tetris", "You play Tetris");
}

void TetrisView::showGameOver() {
  QMessageBox::information(this, "Game Over",
                           "Your score: " + QString::number(game.score));
  close();
}

void TetrisView::showGameOver2() {
  QMessageBox::information(this, "Goodbye", "See you later!");
  close();
}

void TetrisView::gameOverCase() {
  QMessageBox msgBox;
  msgBox.setText("Game Over! Press Q to quit.");
  msgBox.setStandardButtons(
      QMessageBox::NoButton);  // Убираем стандартные кнопки
  msgBox.addButton("Quit", QMessageBox::RejectRole);  // Кнопка "Quit"

  int result = msgBox.exec();  // Показываем диалог и ждем выбора пользователя

  if (result == QMessageBox::RejectRole) {
    QApplication::quit();  // Выход из приложения
  }
}

int TetrisView::ReadHighScore(const std::string &filename) {
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
      out << 0;
      file.close();
      high_score = 0;
    } else {
      qWarning() << "Не удалось создать файл:" << file.errorString();
    }
  }

  return high_score;
}

void TetrisView::WriteHighScore(const std::string &filename) {
  if (game.score > game.high_score) {
    QFile file(QString::fromStdString(filename));
    if (file.open(QIODevice::WriteOnly | QIODevice::Text)) {
      QTextStream out(&file);
      out << game.score;
      file.close();
      game.high_score = game.score;
    } else {
      qWarning() << "Не удалось открыть файл для записи:" << file.errorString();
    }
  }
}
