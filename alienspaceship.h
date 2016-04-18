#ifndef ALIENSPACESHIP_H
#define ALIENSPACESHIP_H

#include "enemy.h"

/**
 * @brief The AlienSpaceship class is a type of enemy.
 */
class AlienSpaceship: public Enemy {

  Q_OBJECT

public:
  /**
   * @brief AlienSpaceship is the default constructor of this enemy type
   * @param initialHealth Inital health of enemy
   * @param w Initial maximum width of enemy
   * @param h Initial maximum height of enemy
   * @param speed Initial speed of enemy
   * @param parent Parent item
   */
  AlienSpaceship(int initialHealth = SPACESHIP_HEALTH, int w = SPACESHIP_MAX_WIDTH,
                 int h = SPACESHIP_MAX_HEIGHT, int speed = SPACESHIP_SPEED,
                 QGraphicsItem * parent = 0): Enemy(initialHealth, w, h, speed, parent) {

    // set the pixmap
    setPixmap(QPixmap(":/images/graphics/starbase/starbase-tex.png").
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
    SPACESHIP_HEALTH = 5,       ///< Health of spaceship
    SPACESHIP_MAX_WIDTH = 300,  ///< Maximum width
    SPACESHIP_MAX_HEIGHT = 300, ///< Maximum height
    SPACESHIP_SPEED = 1,        ///< Speed

  };

};

#endif // ALIENSPACESHIP_H
