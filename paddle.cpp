#include <iostream>
#include "paddle.h"

Paddle::Paddle() {

  dx = 0;
  //image.load("paddle.png");//если грузить картинку
  //длина, высота,формат.
  image = QImage(50, 10, QImage::Format_ARGB32);
  image.fill(Qt::yellow);


  rect = image.rect();//размер платформы = размеру изображения
  resetState();
}

Paddle::~Paddle() {

 std::cout << ("Paddle deleted") << std::endl;
}

void Paddle::setDx(int x) {
  dx = x;
}
//перемещает прямоугольник с изображением платформы. Направление движения задается переменной dx
void Paddle::move() {

    int x = rect.x() + dx;//текущее положение+dx
    int y = rect.top();//платформа не двигается по вертикали
    //Заметка,если хочется, чтобы платфрома двигалась также и по вертикали, ввести dx2, который будет изменяться независимо

    rect.moveTo(x, y);
}

void Paddle::resetState() {//установка платформы в исходное положение

  rect.moveTo(INITIAL_X, INITIAL_Y);
}

QRect Paddle::getRect() {

  return rect;
}

QImage & Paddle::getImage() {

  return image;
}
