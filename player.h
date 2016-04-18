#ifndef PLAYER_H
#define PLAYER_H

#include <QGraphicsPixmapItem>
#include <sprite.h>

class QTimer;

/**
 * @brief The Player class represents the player object
 */
class Player: public Sprite {

  Q_OBJECT

public:
  /**
   * @brief Player Player constructor
   * @param initialHealth Initial health
   * @param speed Speed
   * @param w Maximum width
   * @param h Maximum height
   * @param parent Parent item
   */
  Player(int initialHealth, int speed, int w = 100, int h = 100, QGraphicsItem * parent = 0);
  /**
   * @brief keyPressEvent Event handler for key presses
   * @param event Key event
   */
  void keyPressEvent(QKeyEvent * event);
  /**
   * @brief mousePressEvent Event handler for mouse presses
   * @param event Mouse press event
   */
  void mousePressEvent(QGraphicsSceneMouseEvent * event);
  /**
   * @brief mouseMoveEvent Event handler for mouse moves
   * @param event Mouse move event
   */
  void mouseMoveEvent(QGraphicsSceneMouseEvent * event);
  /**
   * @brief keyReleaseEvent Event handler for key releases
   * @param event Key event
   */
  void keyReleaseEvent(QKeyEvent * event);
  /**
   * @brief die is called when the player dies
   */
  void die() {
    emit theKingIsDead();
  }
  /**
   * @brief move Since player can move differently by mouse and keyboard we don't implement this.
   * @details This empty function has to be present since it is abstract in Sprite
   */
  void move() {

  }
  /**
   * @brief getMissileCount Get the current missile count
   * @return Missile count
   */
  int getMissileCount() const {
    return missileCount;
  }

public slots:
  /**
   * @brief gotHit Slot called when the player gets hit by an enemy
   */
  void gotHit();
  /**
   * @brief getBonus Slot called when the player gets hit by a bonus item
   */
  void getBonus();

signals:
  /**
   * @brief shoot Signal emitted when a shot is performed
   * @param x X position of new missile
   * @param y Y position of new missile
   */
  void shoot(int x, int y);
  /**
   * @brief emptyGun signal emitted when we want to shoot and there are no missiles
   */
  void emptyGun();
  /**
   * @brief theKingIsDead Signal emitted when the player dies (zero health)
   */
  void theKingIsDead();
  /**
   * @brief missileCountChanged Signal emitted when the missile count changes
   * @param c New missile count
   */
  void missileCountChanged(int c);

private slots:
  /**
   * @brief movementAnimation Slot for performing movement animation
   */
  void movementAnimation();

private:
  /**
   * @brief moveRightAnimation Animates move to the right
   * @param animationCounter Image to be displayed
   */
  void moveRightAnimation(const int animationCounter);
  /**
   * @brief moveLeftAnimation Animates move to the left
   * @param animationCounter Image to be displayed
   */
  void moveLeftAnimation(const int animationCounter);
  /**
   * @brief decreaseMissileCount Decreases missile count when a shot is performed
   */
  void decreaseMissileCount() {
    missileCount--;
    emit missileCountChanged(missileCount);
  }
  /**
   * @brief The MoveDirection enum Specifies current movement of player
   */
  enum MoveDirection {
    PLAYER_MOVING_RIGHT,  ///< Player is moving right
    PLAYER_MOVING_LEFT,   ///< Player is moving left
    PLAYER_STANDING,      ///< Player is not moving
  };
  /**
   * @brief Private constants
   */
  enum {
    INITIAL_MISSILE_COUNT = 50, ///< Initial number of missiles
    ANIMATION_PERIOD = 100,     ///< Period in ms of movement animation
  };
  /**
   * @brief moveDirection Current direction of movement used by animation functions
   */
  MoveDirection moveDirection;
  /**
   * @brief missileCount Number of missiles player has
   */
  int missileCount;

};

#endif // PLAYER_H
