#ifndef DARKINVADER_H
#define DARKINVADER_H

#include "enemy.h"

class DarkInvader: public Enemy {
public:
  DarkInvader(int initialHealth = 3, int w = 200, int h = 200, int speed = 2,
              QGraphicsItem * parent = 0): Enemy(initialHealth, w, h, speed, parent) {

    setPixmap(QPixmap(":/images/graphics/spaceship3/tribase-u2-d0.png").
              scaled(QSize(w, h),Qt::KeepAspectRatio));
  }
};

#endif // DARKINVADER_H
