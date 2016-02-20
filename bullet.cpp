#include "bullet.h"
#include <QTimer>

Bullet::Bullet()
{

  // draw rectangle
  setRect(0, 0, 10, 50);

  QTimer * timer = new QTimer();
  connect(timer, SIGNAL(timeout()), this, SLOT(move()));

  // bullet moves every 50 ms
  timer->start(50);
}

void Bullet::move()
{
  // move bullet up
  setPos(x(), y()-10);
}
