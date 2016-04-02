#ifndef ALIENSPACESHIP_H
#define ALIENSPACESHIP_H

#include "enemy.h"

class AlienSpaceship: public Enemy {
public:
  AlienSpaceship(int initialHealth = 5, int w = 300, int h = 300, int speed = 1,
              QGraphicsItem * parent = 0): Enemy(initialHealth, w, h, speed, parent) {

    setPixmap(QPixmap(":/images/graphics/starbase/starbase-tex.png").
              scaled(QSize(w, h),Qt::KeepAspectRatio));
  }
};

#endif // ALIENSPACESHIP_H
