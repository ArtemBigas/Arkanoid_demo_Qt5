#pragma once

#include <QImage>
#include <QRect>

class Paddle {//платформа

  public:
    Paddle();
    ~Paddle();

  public:
    void resetState();
    void move();
    void setDx(int);
    QRect getRect();
    QImage & getImage();

  private:
    QImage image;
    QRect rect;
    int dx;
    //начальные координаты платформы
    static const int INITIAL_X = 200;
    static const int INITIAL_Y = 360;
};
