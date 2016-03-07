#ifndef ENEMY_H
#define ENEMY_H

#include <QGraphicsPixmapItem>
#include <sprite.h>

class Health;
class QTimer;

class Enemy: public Sprite {
  Q_OBJECT

public:

  Enemy(int initialHealth, int speed = 10, int w = 100, int h = 100, QGraphicsItem * parent = 0);
  ~Enemy();

  void die();

public slots:
  void move();

private slots:
  void dieAnimation();

private:

  static const int typesOfEnemies = 2;
  QTimer * timer;
  QTimer * explodeAnimationTimer;

};

#endif // ENEMY_H
