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
    QTransform transform;
    QTransform trans = transform.rotate(0);
    QPixmap transPixmap = QPixmap(pixmap.transformed(trans));

    transPixmap = transPixmap.scaled(QSize(100, 100),Qt::KeepAspectRatio);
    setPixmap(transPixmap);
  } else {
    setPixmap(QPixmap(":/images/graphics/spaceship2/redshipr.png").
              scaled(QSize(100, 100),Qt::KeepAspectRatio));
  }

  setTransformOriginPoint(50,50);
  if (randomNumber % typesOfEnemies) {
    setRotation(90);
  } else {
    setRotation(270);
  }

  timer = new QTimer();
  connect(timer, SIGNAL(timeout()), this, SLOT(move()));

  // bullet moves every 50 ms
  timer->start(50);
}

Enemy::~Enemy() {
  // delete the move timer
  delete timer;
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
