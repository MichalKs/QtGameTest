#ifndef BULLET_H
#define BULLET_H

#include "sprite.h"
#include <QDebug>

/**
 * @brief The Bullet class represents the missiles fired by the player
 */
class Bullet : public Sprite {

  Q_OBJECT

public:
  /**
   * @brief Bullet Construcor of the bullet
   * @param x X position
   * @param y Y position
   * @param w Maximum width
   * @param h Maximum height
   * @param initialSpeed Initial speed
   * @param parent Parent item
   */
  Bullet(int x, int y, int w = BULLET_WIDTH, int h = BULLET_WIDTH,
         int initialSpeed = BULLET_SPEED, QGraphicsItem *parent = 0);

signals:
  /**
   * @brief bulletHitTarget is called whenever bullet hits the target
   * @param casualty The hit item
   */
  void bulletHitTarget(QGraphicsItem * casualty);

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
    BULLET_WIDTH    = 100,  ///< Maximum width
    BULLET_HEIGHT   = 100,  ///< Maximum height
    BULLET_SPEED    = 10,   ///< Speed of bullet
    BULLET_HEALTH   = 1,    ///< This is just because Sprite needs it
    MOVE_TIMEOUT_MS = 50,   ///< Move function called every x ms
  };
  /**
   * @brief collisionDetected
   * @return True if collision is detected, false otherwise
   */
  bool collisionDetected();

};

#endif // BULLET_H
