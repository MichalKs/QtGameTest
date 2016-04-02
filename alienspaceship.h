#ifndef ALIENSPACESHIP_H
#define ALIENSPACESHIP_H

#include "enemy.h"

/**
 * @brief The AlienSpaceship class is a type of enemy.
 */
class AlienSpaceship: public Enemy {
public:
  AlienSpaceship(int initialHealth = 5, int w = 300, int h = 300, int speed = 1,
              QGraphicsItem * parent = 0): Enemy(initialHealth, w, h, speed, parent) {

    setPixmap(QPixmap(":/images/graphics/starbase/starbase-tex.png").
              scaled(QSize(w, h),Qt::KeepAspectRatio));
  }

protected slots:
  /**
   * @brief dieAnimation Called by animationTimer to perform animation of death
   */
  void dieAnimation();

};

#endif // ALIENSPACESHIP_H
