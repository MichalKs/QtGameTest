#include "bullet.h"
#include <QTimer>
#include <QGraphicsScene>
#include <QDebug>
#include <QList>
#include "enemy.h"
#include <typeinfo>
#include "game.h"
#include "score.h"

// remove this
extern Game * game;

/**
 * @brief Bullet::Bullet
 * @param parent
 */
Bullet::Bullet(QGraphicsItem *parent): QObject(), QGraphicsPixmapItem(parent)
{
  // draw graphics
  setPixmap(
        QPixmap(":/images/graphics/missile/rocket-146109_640.png").
        scaled(QSize(width, height),Qt::KeepAspectRatio));

  // create timer for moving
  QTimer * timer = new QTimer();
  connect(timer, SIGNAL(timeout()), this, SLOT(move()));

  // bullet moves every 50 ms
  timer->start(moveTimeoutMs);

  connect(this, SIGNAL(enemyKilled()), game, SLOT(enemyKilled()));

}

/**
 * @brief Bullet::move
 */
void Bullet::move() {

  // check for collision with enemy
  QList<QGraphicsItem *> collidingItemsList = collidingItems();

  for (int i = 0, n = collidingItemsList.size(); i < n; i++) {
    if(typeid(*(collidingItemsList[i])) == typeid(Enemy)) {

      // signalize that enemy has been killed
      emit enemyKilled();

      // cast to Enemy and call die function which will play animation
      // and destroy enemy

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
  setPos(x(), y()-speed);

  // if out of screen destroy the bullet
  if (pos().y() < 0) {
    scene()->removeItem(this);
    delete this;
  }
}
