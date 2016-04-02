#ifndef REDENEMY_H
#define REDENEMY_H

#include "enemy.h"

class RedEnemy: public Enemy {
public:
  RedEnemy(int initialHealth = 2, int w = 100, int h = 100, int speed = 5,
              QGraphicsItem * parent = 0): Enemy(initialHealth, w, h, speed, parent) {

    setPixmap(QPixmap(":/images/graphics/spaceship2/redshipr.png").
              scaled(QSize(w, h),Qt::KeepAspectRatio));
  }
};

#endif // REDENEMY_H
