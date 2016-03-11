#include "bullet.h"
#include <QTimer>
#include <QGraphicsScene>
#include <QDebug>
#include <QList>
#include "enemy.h"
#include <typeinfo>

/**
 * @brief Bullet::Bullet
 * @param x Initial X position
 * @param y Initial Y position
 * @param parent
 */
Bullet::Bullet(int x, int y, QGraphicsItem *parent):
  QObject(), QGraphicsPixmapItem(parent) {

  // draw graphics
  setPixmap(
        QPixmap(":/images/graphics/missile/rocket-146109_640.png").
        scaled(QSize(width, height),Qt::KeepAspectRatio));

  // create timer for moving the bullet
  QTimer * timer = new QTimer();
  connect(timer, SIGNAL(timeout()), this, SLOT(move()));

  // bullet moves every 50 ms
  timer->start(moveTimeoutMs);

  // set initial position
  setPos(x,y);

}

Bullet::~Bullet() {
  qDebug() << "Bullet removed";
}

/**
 * @brief Bullet::move
 */
void Bullet::move() {

  if (collisionDetected()) {
    return;
  }

  // move bullet up
  setPos(x(), y()-speed);

  // if out of screen destroy the bullet
  if (y() < 0) {
    scene()->removeItem(this);
    delete this;
  }
}

bool Bullet::collisionDetected() {
  // check for collision with enemy
  QList<QGraphicsItem*> collidingItemsList = collidingItems();

  // scan list for enemies
  for (int i = 0, n = collidingItemsList.size(); i < n; i++) {
    // if an enemy is found
    if(typeid(*(collidingItemsList[i])) == typeid(Enemy)) {

      // signalize that enemy has been killed
      emit bulletHitTarget(collidingItemsList[i]);

      // TODO cast to Enemy and call die function which will play animation
      // and destroy enemy

      // remove both bullet from scene
      scene()->removeItem(this);
      // delete the objects
      delete this;
      return true;
    }
  }

  return false;
}
