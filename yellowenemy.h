#ifndef YELLOWENEMY_H
#define YELLOWENEMY_H

#include "enemy.h"

class YellowEnemy: public Enemy {
public:
  YellowEnemy(int initialHealth, int w = 100, int h = 100, int speed = 5,
              QGraphicsItem * parent = 0): Enemy(initialHealth, w, h, speed, parent) {


  }
};

#endif // YELLOWENEMY_H
