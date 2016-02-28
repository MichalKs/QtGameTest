#include "enemy.h"
#include <QTimer>
#include <QDebug>
#include <QGraphicsScene>
#include "game.h"
#include <stdlib.h>
#include <QTransform>

// make subclasses for different types of enemy
Enemy::Enemy(int initialHealth, QGraphicsItem * parent):
  QGraphicsPixmapItem(parent) {

  // set initial health
  health = initialHealth;

  // set random position
  int randomNumber = rand() % 700;
  setPos(randomNumber, 0);

  // every enemy created will have to have its own drawing pattern
  // called in constructor - virtual draw() function

  if (randomNumber % typesOfEnemies) {
    QPixmap  pixmap = QPixmap
        (":/images/graphics/spaceship1/ospaceship-main.png");
//    QTransform transform;
//    QTransform trans = transform.rotate(0);
//    QPixmap transPixmap = QPixmap(pixmap.transformed(trans));

//    transPixmap = transPixmap.scaled(QSize(100, 100),Qt::KeepAspectRatio);
    setPixmap(QPixmap(":/images/graphics/spaceship1/ospaceship-main.png").
              scaled(QSize(100, 100),Qt::KeepAspectRatio));
  } else {
    setPixmap(QPixmap(":/images/graphics/spaceship2/redshipr.png").
              scaled(QSize(100, 100),Qt::KeepAspectRatio));
  }

//  setTransformOriginPoint(50,50);
  if (randomNumber % typesOfEnemies) {
//    setRotation(90);
  } else {
//    setRotation(270);
  }

  timer = new QTimer();
  connect(timer, SIGNAL(timeout()), this, SLOT(move()));

  // bullet moves every 50 ms
  timer->start(50);

  explodeAnimationTimer = new QTimer();
  connect(explodeAnimationTimer, SIGNAL(timeout()), this, SLOT(dieAnimation()));

}

Enemy::~Enemy() {

  qDebug() << "Enemy removed";

  // delete the move timer
  delete timer;
  delete explodeAnimationTimer;
}

void Enemy::die() {
  qDebug() << "Im dying. Help!";
  timer->stop();
  explodeAnimationTimer->start(50);

}

void Enemy::decreaseHealth() {
  health--;
}

void Enemy::move() {
  // move enemy down
  setPos(x(), y()+5);

  if (pos().y() > 600) {
    // decrease health
    scene()->removeItem(this);
    delete this;
  }
}

void Enemy::dieAnimation() {

  static int animationCounter;

  switch (animationCounter) {
  case 0:
    setPixmap(QPixmap(":/images/graphics/explosion/explosion/greenexplosion/greenexplosion/Explosion_001.png").
              scaled(QSize(100, 100),Qt::KeepAspectRatio));
    break;
  case 1:
    setPixmap(QPixmap(":/images/graphics/explosion/explosion/greenexplosion/greenexplosion/Explosion_002.png").
              scaled(QSize(100, 100),Qt::KeepAspectRatio));
    break;
  case 2:
    setPixmap(QPixmap(":/images/graphics/explosion/explosion/greenexplosion/greenexplosion/Explosion_003.png").
              scaled(QSize(100, 100),Qt::KeepAspectRatio));
    break;
  case 3:
    setPixmap(QPixmap(":/images/graphics/explosion/explosion/greenexplosion/greenexplosion/Explosion_004.png").
              scaled(QSize(100, 100),Qt::KeepAspectRatio));
    break;
  case 4:
    setPixmap(QPixmap(":/images/graphics/explosion/explosion/greenexplosion/greenexplosion/Explosion_005.png").
              scaled(QSize(100, 100),Qt::KeepAspectRatio));
    break;
  case 5:
    setPixmap(QPixmap(":/images/graphics/explosion/explosion/greenexplosion/greenexplosion/Explosion_006.png").
              scaled(QSize(100, 100),Qt::KeepAspectRatio));
    break;
  case 6:
    setPixmap(QPixmap(":/images/graphics/explosion/explosion/greenexplosion/greenexplosion/Explosion_007.png").
              scaled(QSize(100, 100),Qt::KeepAspectRatio));
    break;
  case 7:
    setPixmap(QPixmap(":/images/graphics/explosion/explosion/greenexplosion/greenexplosion/Explosion_008.png").
              scaled(QSize(100, 100),Qt::KeepAspectRatio));
    break;
  case 8:
    setPixmap(QPixmap(":/images/graphics/explosion/explosion/greenexplosion/greenexplosion/Explosion_009.png").
              scaled(QSize(100, 100),Qt::KeepAspectRatio));
    break;
  case 9:
    setPixmap(QPixmap(":/images/graphics/explosion/explosion/greenexplosion/greenexplosion/Explosion_010.png").
              scaled(QSize(100, 100),Qt::KeepAspectRatio));
    break;
  case 10:
    setPixmap(QPixmap(":/images/graphics/explosion/explosion/greenexplosion/greenexplosion/Explosion_011.png").
              scaled(QSize(100, 100),Qt::KeepAspectRatio));
    break;
  case 11:
    setPixmap(QPixmap(":/images/graphics/explosion/explosion/greenexplosion/greenexplosion/Explosion_012.png").
              scaled(QSize(100, 100),Qt::KeepAspectRatio));
    break;
  case 12:
    setPixmap(QPixmap(":/images/graphics/explosion/explosion/greenexplosion/greenexplosion/Explosion_013.png").
              scaled(QSize(100, 100),Qt::KeepAspectRatio));
    break;
  case 13:
    setPixmap(QPixmap(":/images/graphics/explosion/explosion/greenexplosion/greenexplosion/Explosion_014.png").
              scaled(QSize(100, 100),Qt::KeepAspectRatio));
    break;
  case 14:
    setPixmap(QPixmap(":/images/graphics/explosion/explosion/greenexplosion/greenexplosion/Explosion_015.png").
              scaled(QSize(100, 100),Qt::KeepAspectRatio));
    break;
  case 15:
    setPixmap(QPixmap(":/images/graphics/explosion/explosion/greenexplosion/greenexplosion/Explosion_016.png").
              scaled(QSize(100, 100),Qt::KeepAspectRatio));
    break;
  case 16:
//    explodeAnimationTimer->stop();
    animationCounter = 0;
    scene()->removeItem(this);
    delete this;
    return;
  }

  animationCounter++;

}
