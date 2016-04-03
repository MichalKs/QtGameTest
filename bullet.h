#ifndef BULLET_H
#define BULLET_H

#include "sprite.h"
#include <QDebug>

class Bullet : public Sprite {

  Q_OBJECT

public:

  Bullet(int x, int y, int w = 100, int h = 100, int initialSpeed = 10, QGraphicsItem *parent = 0);

  ~Bullet() {
    qDebug() << "Bullet removed";
  }

signals:
  void bulletHitTarget(QGraphicsItem * casualty);

private slots:
  void move();

private:

  enum {
    BULLET_HEALTH = 1, ///< This is just because Sprite needs it
    MOVE_TIMEOUT_MS = 50, ///< Move function called every x ms
  };

  bool collisionDetected();

};

#endif // BULLET_H
