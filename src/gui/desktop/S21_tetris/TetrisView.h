#ifndef TETRISVIEW_H
#define TETRISVIEW_H

#include <QWidget>
#include <QTimer>
#include <QKeyEvent>
#include <QPainter>
#include <QFile>
#include <QTextStream>
#include <QDebug>
#include "../../../brick_game/tetris/tetris.h" // Подключение вашего кода на C

class TetrisView : public QWidget {
    Q_OBJECT

public:
    TetrisView(QWidget *parent = nullptr);
    ~TetrisView();

protected:
    void paintEvent(QPaintEvent *event) override; // Отрисовка игры
    void keyPressEvent(QKeyEvent *event) override; // Обработка клавиш

private slots:
    void updateGame(); // Обновление состояния игры

private:
    GameInfo_t game; // Состояние игры
    TetFigure figure; // Текущая фигура
    QTimer *timer; // Таймер для обновления игры
    bool running; // Флаг работы игры
    int ReadHighScore(const std::string& filename); // считывание личшего счета
    void WriteHighScore(const std::string& filename);  // запись и создание лучшего счета
    void renderGame(); // Отрисовка игрового поля
    void renderNextFigure(QPainter *painter); // Отрисовка следующей фигуры
    void showMenu(); // Отображение меню
    void showGameOver(); // Отображение экрана завершения игры
    void showGameOver2(); // Альтернативный экран завершения игры
    bool handleMenuInput(); // Обработка ввода в меню
    void gameOverCase(); // Обработка завершения игры
};

#endif // TETRISVIEW_H
