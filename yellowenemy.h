#ifndef YELLOWENEMY_H
#define YELLOWENEMY_H

#include "enemy.h"

/**
 * @brief The YellowEnemy class is a type of enemy.
 */
class YellowEnemy: public Enemy {

  Q_OBJECT

public:
  /**
   * @brief YellowEnemy is the default constructor of this enemy type
   * @param initialHealth Inital health of enemy
   * @param w Initial maximum width of enemy
   * @param h Initial maximum height of enemy
   * @param speed Initial speed of enemy
   * @param parent Parent item
   */
  YellowEnemy(int initialHealth = YELLOW_ENEMY_HEALTH, int w = YELLOW_ENEMY_MAX_WIDTH,
              int h = YELLOW_ENEMY_MAX_HEIGHT, int speed = YELLOW_ENEMY_SPEED,
              QGraphicsItem * parent = 0): Enemy(initialHealth, w, h, speed, parent) {

    setPixmap(QPixmap(":/images/graphics/spaceship1/ospaceship-main.png").
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
    YELLOW_ENEMY_HEALTH = 1,       ///< Health of spaceship
    YELLOW_ENEMY_MAX_WIDTH = 100,  ///< Maximum width
    YELLOW_ENEMY_MAX_HEIGHT = 100, ///< Maximum height
    YELLOW_ENEMY_SPEED = 5,        ///< Speed

  };
};

#endif // YELLOWENEMY_H
