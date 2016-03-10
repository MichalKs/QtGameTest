#include "enemy.h"
#include <QTimer>
#include <QDebug>
#include <QGraphicsScene>
#include "game.h"
#include <stdlib.h>
#include <QTransform>

// make subclasses for different types of enemy
Enemy::Enemy(int initialHealth, int speed, int w, int h, QGraphicsItem * parent):
  Sprite(initialHealth, speed, w, h, parent) {

  // set random position
  int randomNumber = rand() % 700;
  setPos(randomNumber, 0);

  // every enemy created will have to have its own drawing pattern
  // called in constructor - virtual draw() function

  //    QTransform transform;
  //    QTransform trans = transform.rotate(0);
  //    QPixmap transPixmap = QPixmap(pixmap.transformed(trans));
  //    transPixmap = transPixmap.scaled(QSize(100, 100),Qt::KeepAspectRatio);
  //  setTransformOriginPoint(50,50);
  //    setRotation(90);


  int temp = randomNumber % typesOfEnemies;
  qDebug() << "Creating enemy number " << temp;

  switch (temp) {

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

  const int numberOfAnimationFrames = 16;
  static int animationCounter;

  QString filename = QString(":/images/graphics/explosion/greenexplosion/Explosion_%1.png").
      arg(animationCounter+1, 3, 10, QChar('0'));

//  qDebug() << filename;

  // if animation is done then remove object from scene and memory
  if (animationCounter == numberOfAnimationFrames) {
    animationCounter = 0;
    scene()->removeItem(this);
    delete this;
  } else {
    setPixmap(QPixmap(filename).
              scaled(QSize(100, 100),Qt::KeepAspectRatio));
  }

  animationCounter++;

}
