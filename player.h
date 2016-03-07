#ifndef PLAYER_H
#define PLAYER_H

#include <QGraphicsPixmapItem>
#include <sprite.h>

class QTimer;

class Player: public Sprite {

  Q_OBJECT

public:

  // ******************** Constructors ********************
  Player(int initialHealth, int speed, int w = 100, int h = 100, QGraphicsItem * parent = 0);


  // ******************** Destructors *********************
  ~Player();

  // ******************** Public functions ****************

  void resize(QSize & size);

  /**
   * @brief keyPressEvent Event handler for key presses
   * @param event Key event
   */
  void keyPressEvent(QKeyEvent * event);
  /**
   * @brief keyReleaseEvent Event handler for key releases
   * @param event Key event
   */
  void keyReleaseEvent(QKeyEvent * event);

  void die() {

  }


signals:


  // ******************** Signals **************************

  /**
   * @brief shoot Signal emitted when a shot is performed
   * @param x X position of new missile
   * @param y Y position of new missile
   */
  void shoot(int x, int y);


private slots:

  // ******************** Slots ****************************

  /**
   * @brief movementAnimation Slot for performing movement animation
   */
  void movementAnimation();


private:

  // ******************** Private functions ********************
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


  // ******************** Private constants ********************
  /**
   * @brief animationPeriod Period in ms of movement animation
   */
  static const int animationPeriod  = 100;

  /**
   * @brief The MoveDirection enum Specifies current movement of player
   */
  enum MoveDirection {
    PLAYER_MOVING_RIGHT,
    PLAYER_MOVING_LEFT,
    PLAYER_STANDING,
  };

  // ******************** Private variables ********************

  /**
   * @brief moveDirection Current direction of movement used by animation functions
   */
  MoveDirection moveDirection;
  /**
   * @brief animationTimer Timer for performing animation of player moves
   */
  QTimer * animationTimer;

};

#endif // PLAYER_H
