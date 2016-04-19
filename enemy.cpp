#include <QDebug>
#include <typeinfo>
#include <QList>
#include "player.h"
#include "enemy.h"
#include "game.h"
#include "gamescene.h"

Enemy::Enemy(int initialHealth, int w, int h, int speed, QGraphicsItem * parent):
  Sprite(initialHealth, speed, w, h, parent) {

  // set random position
  int possiblePositions = GameScene::SCENE_WIDTH - w;
  int randomNumber = rand() % possiblePositions;
  setPos(randomNumber, 0);

  // create move timer
  moveTimer = new QTimer(this);
  connect(moveTimer, SIGNAL(timeout()), this, SLOT(move()));
  // bullet moves every 50 ms
  moveTimer->start(MOVE_TIMEOUT);

  // create animation timer
  animationTimer = new QTimer(this);
  connect(animationTimer, SIGNAL(timeout()), this, SLOT(dieAnimation()));

}

bool Enemy::collisionDetected() {

//  GameScene * s = dynamic_cast<GameScene*> (scene());
//  if (!s) {
//    return false;
//  }
//  QList<Sprite*> collidingItemsList = s->getSpriteList();

  // check for collision with player
  QList<QGraphicsItem*> collidingItemsList = collidingItems();

  // scan list for enemies
  for (int i = 0, n = collidingItemsList.size(); i < n; i++) {
    // if an enemy is found
    QGraphicsItem * item = collidingItemsList[i];

    if(dynamic_cast<Player*>(item)) {

      die();
      // signalize that enemy has hit player
      emit enemyHitTarget();
      return true;
    }
  }

  return false;
//  GameScene * s = dynamic_cast<GameScene*> (QGraphicsItem::scene());
//  QList<Sprite*> collidingItemsList = s->getSpriteList();

//  for (int i = 0, n = collidingItemsList.size(); i < n; i++) {
//    // if an enemy is found
//    if(typeid(collidingItemsList[i]) == typeid(Player*)) {

//      die();
//      // signalize that enemy has hit player
//      emit enemyHitTarget();
//      return true;
//    }
//  }

//  return false;
}

void Enemy::die() {
  moveTimer->stop();
  animationTimer->start(ANIMATION_TIMEOUT);

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
