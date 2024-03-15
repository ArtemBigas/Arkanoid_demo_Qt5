#include <iostream>
#include "brick.h"

Brick::Brick(int x, int y) {

  //image.load("brickie.png");
    //длина, высота,формат каждого кирпича
    image = QImage(10, 10, QImage::Format_ARGB32);
    image.fill(Qt::red);
  destroyed = false;//если true,кирпич уничтожен
  rect = image.rect();//размер кирпича = размеру изображения
  rect.translate(x, y);//сдвиг прямоугольника на координаты (x, y)
}

Brick::~Brick() {

  std::cout << ("Brick deleted") << std::endl;
}

QRect Brick::getRect() {

  return rect;
}

void Brick::setRect(QRect rct) {

  rect = rct;
}

QImage & Brick::getImage() {

  return image;
}

bool Brick::isDestroyed() {//если destroyed=true кирпич удаляется

  return destroyed;
}

void Brick::setDestroyed(bool destr) {

  destroyed = destr;
}
