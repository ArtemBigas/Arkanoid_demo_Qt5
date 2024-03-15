#include <QPainter>
#include <QApplication>
#include "breakout.h"

Breakout::Breakout(QWidget *parent)
    : QWidget(parent) {

  x = 0;
  gameOver = false;
  gameWon = false;
  paused = false;
  gameStarted = false;
  ball = new Ball();
  paddle = new Paddle();

  int k = 0;
//создаем 60 кирпичей,равно переменной N_OF_BRICKS
  for (int i=0; i<5; i++) {//количество рядов вниз
    for (int j=0; j<12; j++) {//количество рядов влево
          //текущая координата умножается на размер блока.+30 и +50 для сдвига с левого верхнего угла
      bricks[k] = new Brick(j*10+80, i*10+50);
      k++;
    }
  }
}

Breakout::~Breakout() {

 delete ball;
 delete paddle;

 for (int i=0; i<N_OF_BRICKS; i++) {
   delete bricks[i];
 }
}

void Breakout::paintEvent(QPaintEvent *e) {//отслеживаем завершение игры

  Q_UNUSED(e);

  QPainter painter(this);

  if (gameOver) {

    finishGame(&painter, "Game lost");

  } else if(gameWon) {

    finishGame(&painter, "Victory");
  }
  else {

    drawObjects(&painter);//отрисовываем объекты
  }
}

void Breakout::finishGame(QPainter *painter, QString message) {//отрисовка сообщения

  QFont font("Times new Roman", 15, QFont::DemiBold);//шрифт,размер шрифта и стиль(полужирный)
  QFontMetrics fm(font);//используется для измерения текста
  int textWidth = fm.width(message);//размер сообщения

  painter->setFont(font);//устанавливает шрифт font для объекта painter
  //определяют высоту и ширину виджета, на котором будет отображаться текст
  int h = height();
  int w = width();

// сдвиг системы координат рисования на половину ширины и высоты виджета. Теперь точка (0,0) будет находиться в центре виджета.
  painter->translate(QPoint(w/2, h/2));
  //метода drawText() отображается текст message. Параметр -textWidth/2 задает положение текста по горизонтали так,
  //чтобы текст был выровнен по центру относительно центра виджета.
  //Параметр 0 указывает на вертикальное положение текста (в данном случае, по вертикали центрирование).
  painter->drawText(-textWidth/2, 0, message);
}

//отрисовывает в окне все объекты игры: Мяч, платформа и Кирпичи, без отрисовки они существуют, но невидимы
void Breakout::drawObjects(QPainter *painter) {

  painter->drawImage(ball->getRect(), ball->getImage());
  painter->drawImage(paddle->getRect(), paddle->getImage());

  for (int i=0; i<N_OF_BRICKS; i++) {
    if (!bricks[i]->isDestroyed()) {
      painter->drawImage(bricks[i]->getRect(), bricks[i]->getImage());
    }
  }
}

void Breakout::timerEvent(QTimerEvent *e) {

  Q_UNUSED(e);

  moveObjects();//двигаем объекты
  checkCollision();//проверяем столкновения
  repaint();//генерируем событие отрисовки
}

void Breakout::moveObjects() {//перемещения объектов Мяч и Ракетка

  ball->autoMove();
  paddle->move();
}

//Когда игрок отпускает кнопку ← или →, то мы присваиваем переменной dx Ракетки значение 0. В результате Ракетка перестает двигаться:
void Breakout::keyReleaseEvent(QKeyEvent *e) {

    int dx = 0;

    switch (e->key()) {
        case Qt::Key_Left:
            dx = 0;
            paddle->setDx(dx);
            break;

        case Qt::Key_Right:
            dx = 0;
            paddle->setDx(dx);
            break;
    }
}

void Breakout::keyPressEvent(QKeyEvent *e) {//нажатие

    int dx = 0;
//Кнопки ← и → перемещают объект Ракетки. Они влияют на значение переменной dx, которое затем будет добавлено к координате х самой Ракетки.
    switch (e->key()) {
    case Qt::Key_Left:

        dx = -1;
        paddle->setDx(dx);

        break;

    case Qt::Key_Right:

        dx = 1;
        paddle->setDx(dx);
        break;

    case Qt::Key_P://Кнопка P ставит игру на паузу

        pauseGame();
        break;

    case Qt::Key_Space://кнопка "Пробел" запускает игру,

        startGame();
        break;

    case Qt::Key_Escape://кнопка Esc завершает работу приложения

        qApp->exit();
        break;

    default:
        QWidget::keyPressEvent(e);
    }
}

void Breakout::startGame() {//сбрасывает состояния объектов ball и paddle; они перемещаются в исходное положение

  if (!gameStarted) {
    ball->resetState();
    paddle->resetState();
//устанавливаем значение флага destroyed равным false для каждого Кирпича, таким образом отображая их в окне
    for (int i=0; i<N_OF_BRICKS; i++) {
      bricks[i]->setDestroyed(false);
    }

    gameOver = false;
    gameWon = false;
    gameStarted = true;
    timerId = startTimer(DELAY);//запускаем таймер
  }
}

void Breakout::pauseGame() {//игра на паузу

  if (paused) {//если кнопка Р была нажата, то отключается

    timerId = startTimer(DELAY);
    paused = false;
  } else {
//если нет, ставим на паузу, убиваем таймер killTimer(timerId);
    paused = true;
    killTimer(timerId);
  }
}

void Breakout::stopGame() {

  killTimer(timerId);//убиваем таймер
 //Если таймер остается активным при закрытии программы, может случиться повторное выполнение слота таймера после закрытия приложения или утечки памяти
  gameOver = true;
  gameStarted = false;
}

void Breakout::victory() {

  killTimer(timerId);
  gameWon = true;
  gameStarted = false;
}

void Breakout::checkCollision() {

  if (ball->getRect().bottom() > BOTTOM_EDGE) {
    stopGame();
  }
//Проверяем количество разрушенных Кирпичей.
  for (int i=0, j=0; i<N_OF_BRICKS; i++) {

    if (bricks[i]->isDestroyed()) {
      j++;
    }
//Если все Кирпичи уничтожены, то мы выиграли
    if (j == N_OF_BRICKS) {
      victory();
    }
  }

  if ((ball->getRect()).intersects(paddle->getRect())) {

    int paddleLPos = paddle->getRect().left();
    int ballLPos = ball->getRect().left();

    int first = paddleLPos + 8;
    int second = paddleLPos + 16;
    int third = paddleLPos + 24;
    int fourth = paddleLPos + 32;
//Если Мяч попадает в верхнюю часть платформы, то меняем направление полета Мяча
    if (ballLPos < first) {
      ball->setXDir(-1);
      ball->setYDir(-1);
    }

    if (ballLPos >= first && ballLPos < second) {
      ball->setXDir(-1);
      ball->setYDir(-1*ball->getYDir());
    }

    if (ballLPos >= second && ballLPos < third) {
       ball->setXDir(0);
       ball->setYDir(-1);
    }

    if (ballLPos >= third && ballLPos < fourth) {
       ball->setXDir(1);
       ball->setYDir(-1*ball->getYDir());
    }

    if (ballLPos > fourth) {
      ball->setXDir(1);
      ball->setYDir(-1);
    }
  }

  for (int i=0; i<N_OF_BRICKS; i++) {

    if ((ball->getRect()).intersects(bricks[i]->getRect())) {

      int ballLeft = ball->getRect().left();
      int ballHeight = ball->getRect().height();
      int ballWidth = ball->getRect().width();
      int ballTop = ball->getRect().top();

      QPoint pointRight(ballLeft + ballWidth + 1, ballTop);
      QPoint pointLeft(ballLeft - 1, ballTop);
      QPoint pointTop(ballLeft, ballTop -1);
      QPoint pointBottom(ballLeft, ballTop + ballHeight + 1);

      if (!bricks[i]->isDestroyed()) {
        if(bricks[i]->getRect().contains(pointRight)) {
           ball->setXDir(-1);
        }
//Если Мяч ударяется о нижнюю часть Кирпича, то мы меняем направление y Мяча — он идет вниз
        else if(bricks[i]->getRect().contains(pointLeft)) {
           ball->setXDir(1);
        }

        if(bricks[i]->getRect().contains(pointTop)) {
           ball->setYDir(1);
        }

        else if(bricks[i]->getRect().contains(pointBottom)) {
           ball->setYDir(-1);
        }

        bricks[i]->setDestroyed(true);
      }
    }
  }
}
