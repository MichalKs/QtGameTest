#include <QDebug>
#include <typeinfo>
#include "player.h"
#include "enemy.h"
#include "game.h"
#include "gamescene.h"

Enemy::Enemy(int initialHealth, int w, int h, int speed, QGraphicsItem * parent):
  Sprite(initialHealth, speed, w, h, parent) {

  // set random position
  int randomNumber = rand() % 700;
  setPos(randomNumber, 0);

  int enemyType = randomNumber % typesOfEnemies;
//  qDebug() << "Creating enemy number " << temp;

  switch (enemyType) {

  case 0:
    setPixmap(QPixmap(":/images/graphics/spaceship1/ospaceship-main.png").
              scaled(QSize(100, 100),Qt::KeepAspectRatio));
    break;
  case 1:
    setPixmap(QPixmap(":/images/graphics/spaceship2/redshipr.png").
              scaled(QSize(100, 100),Qt::KeepAspectRatio));
    break;
  case 2:
    setPixmap(QPixmap(":/images/graphics/spaceship3/tribase-u2-d0.png").
              scaled(QSize(200, 200),Qt::KeepAspectRatio));
    break;
  case 3:
    setPixmap(QPixmap(":/images/graphics/starbase/starbase-tex.png").
              scaled(QSize(200, 200),Qt::KeepAspectRatio));
    break;
  default:
    setPixmap(QPixmap(":/images/graphics/spaceship1/ospaceship-main.png").
              scaled(QSize(100, 100),Qt::KeepAspectRatio));

  }

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

void Enemy::dieAnimation() {

  const int numberOfAnimationFrames = 16;
  static int animationCounter;

  QString filename = QString(":/images/graphics/explosion/greenexplosion/Explosion_%1.png").
      arg(animationCounter+1, 3, 10, QChar('0'));

//  qDebug() << filename;

  // if animation is done then remove object from scene and memory
  if (animationCounter == numberOfAnimationFrames) {
    animationCounter = 0;
    GameScene * s = dynamic_cast<GameScene*> (QGraphicsItem::scene());
    s->removeItem(this);
    delete this;
  } else {
    setPixmap(QPixmap(filename).
              scaled(QSize(100, 100),Qt::KeepAspectRatio));
  }

  animationCounter++;

}
