#pragma once

#include <QImage>
#include <QRect>

class Ball {

  public:
    Ball();
    ~Ball();

  public:
    void resetState();
    void autoMove();
    void setXDir(int);
    void setYDir(int);
    int getXDir();
    int getYDir();
    QRect getRect();
    QImage & getImage();

  private:
    //xdir и ydir - направления движения мяча
    int xdir;
    int ydir;
    QImage image;
    QRect rect;
    //0 в координатах - левый верхний угол
    static const int INITIAL_X = 230;
    static const int INITIAL_Y = 355;
    static const int RIGHT_EDGE = 300;
};
