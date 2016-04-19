#include "bullet.h"
#include "enemy.h"
#include "gamescene.h"
#include <QTimer>
#include <QDebug>
#include <QList>
#include <typeinfo>

Bullet::Bullet(int x, int y, int w, int h, int initialSpeed, QGraphicsItem * parent):
  Sprite(BULLET_HEALTH, initialSpeed, w, h, parent) {

  // draw graphics
  setPixmap(
        QPixmap(":/images/graphics/missile/rocket-146109_640.png").
        scaled(QSize(w, h),Qt::KeepAspectRatio));

  // set initial position
  setPos(x,y);

  // create timer for moving the bullet
  QTimer * timer = new QTimer(this);
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
    GameScene * s = dynamic_cast<GameScene*> (QGraphicsItem::scene());
    // remove bullet from scene
    s->removeItem(this);
    delete this;
  }
}

bool Bullet::collisionDetected() {

  // check for collision with enemy
  QList<QGraphicsItem*> collidingItemsList = collidingItems();

  // scan list for enemies
  for (QList<QGraphicsItem*>::Iterator it = collidingItemsList.begin();
       it != collidingItemsList.end();
       ++it) {

    // if an enemy is found
    Enemy * enemy = dynamic_cast<Enemy*>(*it);

    if(enemy) {

      // signalize that enemy has been killed
      emit bulletHitTarget(*it);
      GameScene * s = dynamic_cast<GameScene*> (QGraphicsItem::scene());
      // remove bullet from scene
      s->removeItem(this);
      // delete the bullet
      delete this;

      return true;
    }
  }

  return false;
}
