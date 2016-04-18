#ifndef ENEMY_H
#define ENEMY_H

#include <sprite.h>
#include <QTimer>

/**
 * @brief The Enemy class represents enemies in the game
 */
class Enemy: public Sprite {

  Q_OBJECT

public:

  /**
   * @brief Enemy Constructor for enemy
   * @param initialHealth Initial health
   * @param speed Speed of enemy
   * @param w Maximum width of enemy
   * @param h Maximum height of enemy
   * @param parent Parent of enemy
   */
  Enemy(int initialHealth = ENEMY_HEALTH, int w = ENEMY_WIDTH,
        int h = ENEMY_HEIGHT, int speed = ENEMY_SPEED,
        QGraphicsItem * parent = 0);
  /**
   * @brief die Function performed before enemy death
   */
  void die();

public slots:
  /**
   * @brief move Move slot is called periodically by move timer
   */
  void move();
  /**
   * @brief pause is called when the game is paused
   */
  void pause() {
    moveTimer->stop();
  }
  /**
   * @brief unpause is called when the game is unpaused
   */
  void unpause() {
    // bullet moves every 50 ms
    moveTimer->start(MOVE_TIMEOUT);
  }

protected slots:
  /**
   * @brief dieAnimation is called by animationTimer to perform animation of death.
   * @details Since every enemy is different this is an abstract function
   */
  virtual void dieAnimation() = 0;

signals:
  /**
   * @brief enemyHitTarget Signal emitted when enemy hits player
   */
  void enemyHitTarget();

private:
  /**
   * @brief Private constants
   */
  enum {
    ENEMY_HEALTH  = 1,    ///< Health
    ENEMY_WIDTH   = 100,  ///< Maximum widht
    ENEMY_HEIGHT  = 100,  ///< Maximum height
    ENEMY_SPEED   = 5,    ///< Speed
    MOVE_TIMEOUT  = 50,   ///< Move timeout period in ms
    ANIMATION_TIMEOUT = 50, ///< Animation period in ms
  };

  /**
   * @brief collisionDetected is a help function for detecting collisions with other objects
   * @return True if collision is detected
   */
  bool collisionDetected();
  /**
   * @brief moveTimer Timer for moving
   */
  QTimer * moveTimer;
  /**
   * @brief animationTimer Timer for animations
   */
  QTimer * animationTimer;

};

#endif // ENEMY_H
