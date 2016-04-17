#include "bonus.h"
#include <QTimer>
#include "gamescene.h"
#include <typeinfo>
#include "player.h"

Bonus::Bonus(int x, int y, int w, int h, int initialSpeed, QGraphicsItem * parent):
  Sprite(BONUS_HEALTH, initialSpeed, w, h, parent) {

  // draw graphics
  setPixmap(
        QPixmap(":/images/graphics/bonus/black.png").
        scaled(QSize(w, h),Qt::KeepAspectRatio));

  // set initial position
  setPos(x,y);

  // create timer for moving the bullet
  QTimer * timer = new QTimer();
  connect(timer, SIGNAL(timeout()), this, SLOT(move()));

  // bonus moves every 50 ms
  timer->start(MOVE_TIMEOUT_MS);

}

void Bonus::move() {
  // check for collisions
  if (collisionDetected()) {
    // return because bullet does not exist anymore
    return;
  }

  // move bullet up
  setPos(x(), y()+getSpeed());

  // if out of screen destroy the bullet
  if (pos().y() > scene()->height()-boundingRect().height()) {
    // decrease health
    GameScene * s = dynamic_cast<GameScene*> (QGraphicsItem::scene());
    s->removeItem(this);
    delete this;
  }
}

bool Bonus::collisionDetected() {
  // check for collision with enemy
  QList<QGraphicsItem*> collidingItemsList = collidingItems();

  // scan list for enemies
  for (int i = 0, n = collidingItemsList.size(); i < n; i++) {
    // if an enemy is found
    if(typeid(*(collidingItemsList[i])) == typeid(Player)) {

      // signalize that bonus has hit player
      emit playerGetsBonus();

      GameScene * s = dynamic_cast<GameScene*> (QGraphicsItem::scene());
      s->removeItem(this);
      delete this;

      return true;
    }
  }

  return false;
}
