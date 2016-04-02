#ifndef YELLOWENEMY_H
#define YELLOWENEMY_H

#include "enemy.h"

/**
 * @brief The YellowEnemy class is a type of enemy.
 */
class YellowEnemy: public Enemy {
public:
  YellowEnemy(int initialHealth = 1, int w = 100, int h = 100, int speed = 5,
              QGraphicsItem * parent = 0): Enemy(initialHealth, w, h, speed, parent) {

    setPixmap(QPixmap(":/images/graphics/spaceship1/ospaceship-main.png").
              scaled(QSize(w, h),Qt::KeepAspectRatio));
  }

protected slots:
  /**
   * @brief dieAnimation Called by animationTimer to perform animation of death
   */
  void dieAnimation();

};

#endif // YELLOWENEMY_H
