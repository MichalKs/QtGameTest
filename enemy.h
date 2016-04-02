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
  Enemy(int initialHealth = 1, int w = 100, int h = 100, int speed = 5,
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
   * @brief pause Pause is called when the game is paused
   */
  void pause() {
    moveTimer->stop();
  }

  /**
   * @brief unpause Unpasue is called when the game is unpaused
   */
  void unpause() {
    // bullet moves every 50 ms
    moveTimer->start(50);
  }

protected slots:
  /**
   * @brief dieAnimation Called by animationTimer to perform animation of death
   */
  virtual void dieAnimation() = 0;

signals:
  /**
   * @brief enemyHitTarget Signal emitted when enemy hits player
   */
  void enemyHitTarget();

private:
  /**
   * @brief collisionDetected Help function for detecting collisions with other objects
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
