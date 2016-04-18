#ifndef BONUS_H
#define BONUS_H

#include "sprite.h"

/**
 * @brief The Bonus class represents a bonus item - for now an extra set of missiles
 * is the only available bonus. If there are others they should probably become subclasses
 * of Bonus
 */
class Bonus : public Sprite {

Q_OBJECT

public:
  /**
   * @brief Bonus Constructor of bonus item
   * @param x X position
   * @param y Y position
   * @param w Maximum width
   * @param h Maximum height
   * @param initialSpeed Initial speed
   * @param parent Parent item
   */
  Bonus(int x, int y, int w = BONUS_WIDTH, int h = BONUS_HEIGHT,
        int initialSpeed = BONUS_SPEED, QGraphicsItem * parent = 0);

signals:
  /**
   * @brief playerGetsBonus is called whenever the player collides with the bonus item
   */
  void playerGetsBonus();

private slots:
  /**
   * @brief move slot is responsible for moving the item
   */
  void move();

private:
  /**
   * @brief Private constants
   */
  enum {
    BONUS_WIDTH     = 50, ///< Maximum width
    BONUS_HEIGHT    = 50, ///< Maximum height
    BONUS_SPEED     = 3,  ///< Speed
    BONUS_HEALTH    = 1,  ///< This is just because Sprite needs it
    MOVE_TIMEOUT_MS = 50, ///< Move function called every x ms
  };
  /**
   * @brief collisionDetected
   * @return True if collision is detected, false otherwise
   */
  bool collisionDetected();

};

#endif // BONUS_H
