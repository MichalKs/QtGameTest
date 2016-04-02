#include <QDebug>
#include <typeinfo>
#include "player.h"
#include "enemy.h"
#include "game.h"
#include "gamescene.h"

Enemy::Enemy(int initialHealth, int w, int h, int speed, QGraphicsItem * parent):
  Sprite(initialHealth, speed, w, h, parent) {

  // set random position
  int possiblePositions = 800 - w;
  int randomNumber = rand() % possiblePositions;
  setPos(randomNumber, 0);

  // create move timer
  moveTimer = new QTimer(this);
  connect(moveTimer, SIGNAL(timeout()), this, SLOT(move()));
  // bullet moves every 50 ms
  moveTimer->start(50);

  // create animation timer
  animationTimer = new QTimer(this);
  connect(animationTimer, SIGNAL(timeout()), this, SLOT(dieAnimation()));

}

bool Enemy::collisionDetected() {
  // check for collision with enemy
  QList<QGraphicsItem*> collidingItemsList = collidingItems();

  // scan list for enemies
  for (int i = 0, n = collidingItemsList.size(); i < n; i++) {
    // if an enemy is found
    if(typeid(*(collidingItemsList[i])) == typeid(Player)) {

      die();
      // signalize that enemy has hit player
      emit enemyHitTarget();
      return true;
    }
  }

  return false;
}

void Enemy::die() {
  qDebug() << "Enemy died";
  moveTimer->stop();
  animationTimer->start(50);

}

void Enemy::move() {

  // move enemy down
  setPos(x(), y()+getSpeed());

  if (pos().y() > scene()->height()-boundingRect().height()) {
    // decrease health
    GameScene * s = dynamic_cast<GameScene*> (QGraphicsItem::scene());
    s->removeItem(this);
    delete this;
  }
  // check for collisions
  collisionDetected();
}
