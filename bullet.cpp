#include "bullet.h"
#include <QTimer>
#include <QGraphicsScene>
#include <QDebug>

Bullet::Bullet()
{

  // draw rectangle
  setRect(0, 0, 10, 50);

  QTimer * timer = new QTimer();
  connect(timer, SIGNAL(timeout()), this, SLOT(move()));

  // bullet moves every 50 ms
  timer->start(50);
}

Bullet::~Bullet()
{
  qDebug() << "Bullet deleted";
}

void Bullet::move()
{
  // move bullet up
  setPos(x(), y()-10);

  if (pos().y() + rect().height() < 0)
  {
    scene()->removeItem(this);
    delete this;
  }
}
