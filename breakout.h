#pragma once

#include <QWidget>
#include <QKeyEvent>
#include "ball.h"
#include "brick.h"
#include "paddle.h"

class Breakout : public QWidget {

  public:
    Breakout(QWidget *parent = 0);
    ~Breakout();

  protected:
    void paintEvent(QPaintEvent *);
    void timerEvent(QTimerEvent *);
    //мы следим за событиями нажатия клавиш клавиатуры с помощью следующих методов keyPressEvent и keyReleaseEvent
    void keyPressEvent(QKeyEvent *);
    void keyReleaseEvent(QKeyEvent *);

    void drawObjects(QPainter *);
    void finishGame(QPainter *, QString);
    void moveObjects();

    void startGame();
    void pauseGame();
    void stopGame();
    void victory();
    void checkCollision();

  private:
    int x;//текущее положение платформы
    int timerId;//отслеживаем таймер, нужен для паузы
    static const int N_OF_BRICKS = 60;//количество кирпичей,не менять,изменять только с конструктором
    static const int DELAY = 10;//скорость игры,чем меньше значение, тем больше скорость
    static const int BOTTOM_EDGE = 400;//нижний край поля
    //Переменные-указатели на объекты Мяча, Ракетки и массива Кирпичей,берутся из соответствующих классов
    Ball *ball;
    Paddle *paddle;
    Brick *bricks[N_OF_BRICKS];
    //4 состояния игры
    bool gameOver;
    bool gameWon;
    bool gameStarted;
    bool paused;
};
