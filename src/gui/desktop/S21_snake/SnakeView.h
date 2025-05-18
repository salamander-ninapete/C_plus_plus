#ifndef SNAKEVIEW_H
#define SNAKEVIEW_H

#include <QMainWindow>
#include <QWidget>
#include <QLabel>
#include <QTimer>
#include <QKeyEvent>
#include <QPainter>
#include <QFile>
#include <QTextStream>
#include <QDebug>
#include "../../../brick_game/snake/SnakeController.h"

class SnakeView : public QMainWindow {
    Q_OBJECT

public:
    SnakeView(s21::SnakeController& controller, QWidget* parent = nullptr);
    ~SnakeView();

    void RenderGame();
    void RenderStartScreen();
    void RenderEndScreen(int score);
    void RenderWinScreen();
    int ReadHighScore(const std::string& filename);
    void WriteHighScore(const std::string& filename);

protected:
    void keyPressEvent(QKeyEvent* event) override;

private slots:
    void UpdateGame();

private:
    s21::SnakeController& controller_;
    time_t lastActionTime_;

    QTimer* gameTimer;
    QLabel* gameFieldLabel;
    QLabel* scoreLabel;
    QLabel* highScoreLabel;
    QLabel* levelLabel;
    QLabel* speedLabel;
    QLabel* statusLabel;
    QLabel* statusLabeltwo;


    void RenderSnakeField();
    void RenderRightPanel();
    void ExitView();
    bool StartMenu();
    void PreView();
};

#endif // SNAKEVIEW_H
