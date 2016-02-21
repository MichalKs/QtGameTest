#include "enemy.h"
#include <QTimer>
#include <QDebug>
#include <QGraphicsScene>
#include "game.h"
#include "health.h"
#include <stdlib.h>

extern Game * game;

Enemy::Enemy(QGraphicsItem * parent): QObject(), QGraphicsRectItem(parent)
{

  // set random position
  int randomNumber = rand() % 700;
  setPos(randomNumber, 0);

  // draw rectangle
  setRect(0, 0, 100, 100);

  QTimer * timer = new QTimer();
  connect(timer, SIGNAL(timeout()), this, SLOT(move()));

  // bullet moves every 50 ms
  timer->start(50);
}

void Enemy::move()
{
  // move enemy down
  setPos(x(), y()+5);

  if (pos().y() > 600)
  {
    // decrease health
    game->health->decrease();
    scene()->removeItem(this);
    delete this;
  }
}
