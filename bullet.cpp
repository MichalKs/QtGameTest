#include "bullet.h"
#include <QTimer>
#include <QGraphicsScene>
#include <QDebug>
#include <QList>
#include "enemy.h"
#include <typeinfo>

//Sprite(int initialHealth, int initialSpeed, int w, int h, QGraphicsItem * parent = 0)
Bullet::Bullet(int x, int y, int w, int h, int initialSpeed, QGraphicsItem * parent):
  Sprite(BULLET_HEALTH, initialSpeed, w, h, parent) {

  // draw graphics
  setPixmap(
        QPixmap(":/images/graphics/missile/rocket-146109_640.png").
        scaled(QSize(w, h),Qt::KeepAspectRatio));

  // set initial position
  setPos(x,y);

  // create timer for moving the bullet
  QTimer * timer = new QTimer();
  connect(timer, SIGNAL(timeout()), this, SLOT(move()));

  // bullet moves every 50 ms
  timer->start(MOVE_TIMEOUT_MS);

}

void Bullet::move() {

  // check for collisions
  if (collisionDetected()) {
    // return because bullet does not exist anymore
    return;
  }

  // move bullet up
  setPos(x(), y()-getSpeed());

  // if out of screen destroy the bullet
  if (y() < 0) {
    scene()->removeItem(this);
    delete this;
  }
}

bool Bullet::collisionDetected() {

  // check for collision with enemy
  QList<QGraphicsItem*> collidingItemsList = collidingItems();

  Enemy * enemy;

  // scan list for enemies
  for (int i = 0, n = collidingItemsList.size(); i < n; i++) {

    // if an enemy is found
    enemy = dynamic_cast<Enemy*>(collidingItemsList[i]);

    if(enemy) {

      // signalize that enemy has been killed
      emit bulletHitTarget(collidingItemsList[i]);
      // remove bullet from scene
      scene()->removeItem(this);
      // delete the bullet
      delete this;

      return true;
    }
  }

  return false;
}
