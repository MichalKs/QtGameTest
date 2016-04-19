#include "bonus.h"
#include "gamescene.h"
#include "player.h"
#include <QTimer>
#include <typeinfo>


Bonus::Bonus(int x, int y, int w, int h, int initialSpeed, QGraphicsItem * parent):
  Sprite(BONUS_HEALTH, initialSpeed, w, h, parent) {

  // draw graphics
  setPixmap(
        QPixmap(":/images/graphics/bonus/black.png").
        scaled(QSize(w, h),Qt::KeepAspectRatio));

  // set initial position
  setPos(x,y);

  // create timer for moving the bullet
  QTimer * timer = new QTimer(this);
  connect(timer, SIGNAL(timeout()), this, SLOT(move()));
  // bonus moves every 50 ms
  timer->start(MOVE_TIMEOUT_MS);

}

void Bonus::move() {
  // check for collisions
  if (collisionDetected()) {
    // return because bonus does not exist anymore
    return;
  }

  // move bonus down
  setPos(x(), y()+getSpeed());

  // if out of screen destroy the bonus
  if (pos().y() > scene()->height()-boundingRect().height()) {
    GameScene * s = dynamic_cast<GameScene*> (QGraphicsItem::scene());
    s->removeItem(this);
    delete this;
  }
}

bool Bonus::collisionDetected() {
  // check for collision with player
  QList<QGraphicsItem*> collidingItemsList = collidingItems();

  // scan list for player
  for (QList<QGraphicsItem*>::Iterator it = collidingItemsList.begin();
       it != collidingItemsList.end();
       ++it) {

    // if an player is found
    Player * player = dynamic_cast<Player*>(*it);

    if(player) {

      // signalize that bonus has hit player
      emit playerGetsBonus();

      // delete bonus
      GameScene * s = dynamic_cast<GameScene*> (QGraphicsItem::scene());
      s->removeItem(this);
      delete this;

      return true;
    }
  }

  return false;
}
