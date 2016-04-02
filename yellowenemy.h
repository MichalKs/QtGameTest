#ifndef YELLOWENEMY_H
#define YELLOWENEMY_H

#include "enemy.h"

class YellowEnemy: public Enemy {
public:
  YellowEnemy(int initialHealth = 1, int w = 100, int h = 100, int speed = 5,
              QGraphicsItem * parent = 0): Enemy(initialHealth, w, h, speed, parent) {

    setPixmap(QPixmap(":/images/graphics/spaceship1/ospaceship-main.png").
              scaled(QSize(w, h),Qt::KeepAspectRatio));
  }
};

#endif // YELLOWENEMY_H
