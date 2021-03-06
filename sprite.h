#ifndef SPRITE_H
#define SPRITE_H

#include <QGraphicsPixmapItem>

/**
 * @brief The Sprite class Abstract class for all sprites on screen to inherit from.
 */
class Sprite: public QObject, public QGraphicsPixmapItem {

  Q_OBJECT

public:

  /**
   * @brief Public constants
   */
  enum {
    MAXIMUM_SPEED = +100, ///< Maximum speed
    MINIMUM_SPEED = -100, ///< Minimum speed
  };

  /**
   * @brief Sprite
   * @details Every sprite has a health that causes sprite to die if it reaches 0.
   * Every sprite has a required width and height (only one of them is respected due to
   * aspect ratio). A sprite also has a speed of movement (if speed is 0 the sprite does not move).
   * @param initialHealth Initial health
   * @param initialSpeed Initial speed
   * @param w Maximum width
   * @param h Maximum height
   * @param parent Parent item
   */
  Sprite(int initialHealth, int initialSpeed, int w, int h, QGraphicsItem * parent = 0):
    QGraphicsPixmapItem(parent), health(initialHealth), speed(initialSpeed),
    maxWidth(w), maxHeight(h) {

  }
  /**
   * @brief die Virtual function for dying before being removed from screen
   */
  virtual void die() {

  }
  /**
   * @brief move Move sprite on scene
   */
  virtual void move() = 0;
  /**
   * @brief ~Sprite Virtual desctructor
   */
  virtual ~Sprite() {

  }
  /**
   * @brief getHealth Getter for health parameter
   * @return Current health of sprite
   */
  int getHealth() {
    return health;
  }
  /**
   * @brief decreaseHealth Inflict damage on sprite
   * @param damage The number of health points subtracted
   */
  void decreaseHealth(int damage = 1) {
    health -= damage;
    emit healthChanged(health);
    if (health <= 0) {
      die();
    }
  }
  /**
   * @brief getSpeed Gets speed
   * @return Speed
   */
  int getSpeed() {
    return speed;
  }
  /**
   * @brief setSpeed Sets speed
   * @param newSpeed new speed
   */
  void setSpeed(int newSpeed) {
    if (newSpeed <= MAXIMUM_SPEED && newSpeed >= MINIMUM_SPEED) {
      speed = newSpeed;
    }
  }
  /**
   * @brief getMaxWidth Gets maximum width
   * @return Maximum width
   */
  int getMaxWidth() {
    return maxWidth;
  }
  /**
   * @brief getMaxHeight Gets maximum height
   * @return Maximum height
   */
  int getMaxHeight() {
    return maxHeight;
  }
  /**
   * @brief pause Pause sprite
   */
  virtual void pause() {
    paused = true;
  }
  /**
   * @brief unpause Unpause sprite
   */
  virtual void unpause() {
    paused = false;
  }

signals:
  /**
   * @brief healthChanged Signal emitted when health changes
   * @param h Changed health
   */
  void healthChanged(int h);

private:
  /**
   * @brief health Every sprite has some health
   * @details When health goes to zero, sprite dies
   */
  int health;
  /**
   * @brief speed Speed in Y coordinates (sprites can only move up and down in this type of game)
   */
  int speed;
  /**
   * @brief width Maximum width of sprite
   */
  int maxWidth;
  /**
   * @brief height Maximum height of sprite
   */
  int maxHeight;
  /**
   * @brief paused If true sprite is standing still
   */
  bool paused;

};

#endif // SPRITE_H
