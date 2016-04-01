#ifndef ENEMY_H
#define ENEMY_H

#include <sprite.h>

class QTimer;
class GameScene;

class Enemy: public Sprite {
  Q_OBJECT

public:

  Enemy(int initialHealth, int speed = 10, int w = 100, int h = 100, QGraphicsItem * parent = 0);
  ~Enemy();

  void die();

public slots:
  void move();
  void pause();
  void unpause();

private slots:
  void dieAnimation();

signals:
  void enemyHitTarget();

private:
  bool collisionDetected();
  static const int typesOfEnemies = 4;
  QTimer * timer;
  QTimer * explodeAnimationTimer;
  GameScene * scene;

};

#endif // ENEMY_H
