#ifndef DARKINVADER_H
#define DARKINVADER_H

#include "enemy.h"

/**
 * @brief The DarkInvader class is a type of enemy.
 */
class DarkInvader: public Enemy {

  Q_OBJECT

public:
  /**
   * @brief DarkInvader is the default constructor of this enemy type
   * @param initialHealth Inital health of enemy
   * @param w Initial maximum width of enemy
   * @param h Initial maximum height of enemy
   * @param speed Initial speed of enemy
   * @param parent Parent item
   */
  DarkInvader(int initialHealth = INVADER_HEALTH, int w = INVADER_MAX_WIDTH,
              int h = INVADER_MAX_HEIGHT, int speed = INVADER_SPEED,
              QGraphicsItem * parent = 0): Enemy(initialHealth, w, h, speed, parent) {

    // set the pixmap
    setPixmap(QPixmap(":/images/graphics/spaceship3/tribase-u2-d0.png").
              scaled(QSize(w, h),Qt::KeepAspectRatio));
  }

protected slots:
  /**
   * @brief dieAnimation is called by animationTimer to perform animation of death
   */
  void dieAnimation();

private:
  /**
   * @brief Private constants
   */
  enum {
    INVADER_HEALTH = 3,       ///< Health of spaceship
    INVADER_MAX_WIDTH = 200,  ///< Maximum width
    INVADER_MAX_HEIGHT = 200, ///< Maximum height
    INVADER_SPEED = 2,        ///< Speed

  };
};

#endif // DARKINVADER_H
