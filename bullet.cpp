#include "bullet.h"
#include <QTimer>
#include <QGraphicsScene>
#include <QDebug>
#include <QList>
#include "enemy.h"
#include <typeinfo>
#include "game.h"
#include "score.h"

extern Game * game;

Bullet::Bullet(QGraphicsItem *parent): QObject(), QGraphicsRectItem(parent)
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

  // check for collision with enemy
  QList<QGraphicsItem *> collidingItemsList = collidingItems();
  int n = collidingItemsList.size();
  for (int i = 0; i < n; i++)
  {
    if(typeid(*(collidingItemsList[i])) == typeid(Enemy))
    {

      // increase the score
      game->score->increase();

      // remove both bullet and Enemy
      scene()->removeItem(collidingItemsList[i]);
      scene()->removeItem(this);
      // delete the objects
      delete collidingItemsList[i];
      delete this;
      return;
    }
  }

  // move bullet up
  setPos(x(), y()-10);

  if (pos().y() + rect().height() < 0)
  {
    scene()->removeItem(this);
    delete this;
  }
}
