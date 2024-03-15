#include <iostream>
#include "ball.h"

Ball::Ball() {
//В начале игры Мяч движется в направлении вправо-вверх
  xdir = 1;
  ydir = -1;

  //image.load("ball.png");
  //длина, высота,формат.
  image = QImage(10, 10, QImage::Format_ARGB32);
  image.fill(Qt::black);

  rect = image.rect();//размер платформы = размеру изображения
  resetState();
}

Ball::~Ball() {

  std::cout << ("Ball deleted") << std::endl;
}

void Ball::autoMove() {

  rect.translate(xdir, ydir);

  if (rect.left() == 0) {//если мяч столкнулся с левой стеной
    xdir = 1;//мяч "ударяется" и движется вправо
  }

  if (rect.right() == RIGHT_EDGE) {//если мяч столкнулся с правой стеной
    xdir = -1;//мяч "ударяется" и движется влево
  }

  if (rect.top() == 0) {//если мяч столкнулся с верхней стеной
    ydir = 1;//начинает двигатся вниз
  }
}

void Ball::resetState() {

  rect.moveTo(INITIAL_X, INITIAL_Y);
}

void Ball::setXDir(int x) {

  xdir = x;
}

void Ball::setYDir(int y) {

  ydir = y;
}

int Ball::getXDir() {

  return xdir;
}

int Ball::getYDir() {

  return ydir;
}

QRect Ball::getRect() {

  return rect;
}

QImage & Ball::getImage() {

  return image;
}
