#include "enemy.h"
#include <QTimer>
#include <QDebug>
#include <QGraphicsScene>
#include "game.h"
#include "health.h"
#include <stdlib.h>
#include <QTransform>

extern Game * game;

Enemy::Enemy(int initialHealth, QGraphicsItem * parent): QGraphicsPixmapItem(parent)
{

  // set initial health
  health = initialHealth;

  // set random position
  int randomNumber = rand() % 700;
  setPos(randomNumber, 0);

  // draw rectangle
//  setRect(0, 0, 100, 100);

  if (randomNumber % 2) {
    QPixmap pixmap = QPixmap(":/images/graphics/spaceship1/ospaceship-main.png");
    QTransform transform;
    QTransform trans = transform.rotate(0);
    QPixmap transPixmap = QPixmap(pixmap.transformed(trans));

    transPixmap = transPixmap.scaled(QSize(100, 100),Qt::KeepAspectRatio);
    setPixmap(transPixmap);
  }
  else
  {
    setPixmap(QPixmap(":/images/graphics/spaceship2/redshipr.png").
              scaled(QSize(100, 100),Qt::KeepAspectRatio));
  }

  setTransformOriginPoint(50,50);
  if (randomNumber % 2) {
    setRotation(90);
  }
  else
  {
    setRotation(270);
  }



  QTimer * timer = new QTimer();
  connect(timer, SIGNAL(timeout()), this, SLOT(move()));

  // bullet moves every 50 ms
  timer->start(50);
}

void Enemy::decreaseHealth()
{
  health--;
}

void Enemy::move()
{
  // move enemy down
  setPos(x(), y()+5);

  if (pos().y() > 600)
  {
    // decrease health
    game->health->decrease(1);
    scene()->removeItem(this);
    delete this;
  }
}
