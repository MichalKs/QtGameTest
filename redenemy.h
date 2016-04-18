#ifndef REDENEMY_H
#define REDENEMY_H

#include "enemy.h"

/**
 * @brief The RedEnemy class is a type of enemy.
 */
class RedEnemy: public Enemy {

  Q_OBJECT

public:
  /**
   * @brief RedEnemy is the default constructor of this enemy type
   * @param initialHealth Inital health of enemy
   * @param w Initial maximum width of enemy
   * @param h Initial maximum height of enemy
   * @param speed Initial speed of enemy
   * @param parent Parent item
   */
  RedEnemy(int initialHealth = RED_ENEMY_HEALTH, int w = RED_ENEMY_MAX_WIDTH,
           int h = RED_ENEMY_MAX_HEIGHT, int speed = RED_ENEMY_SPEED,
           QGraphicsItem * parent = 0): Enemy(initialHealth, w, h, speed, parent) {

    setPixmap(QPixmap(":/images/graphics/spaceship2/redshipr.png").
              scaled(QSize(w, h),Qt::KeepAspectRatio));
  }

protected slots:
  /**
   * @brief dieAnimation Called by animationTimer to perform animation of death
   */
  void dieAnimation();

private:
  /**
   * @brief Private constants
   */
  enum {
    RED_ENEMY_HEALTH = 2,       ///< Health of spaceship
    RED_ENEMY_MAX_WIDTH = 100,  ///< Maximum width
    RED_ENEMY_MAX_HEIGHT = 100, ///< Maximum height
    RED_ENEMY_SPEED = 5,        ///< Speed

  };
};

#endif // REDENEMY_H
