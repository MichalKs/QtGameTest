#ifndef BONUS_H
#define BONUS_H

#include "sprite.h"

class Bonus : public Sprite {

Q_OBJECT

public:
  Bonus(int x, int y, int w = 50, int h = 50, int initialSpeed = 3, QGraphicsItem *parent = 0);

signals:
  void playerGetsBonus();

private slots:
  void move();

private:
  enum {
    BONUS_HEALTH = 1, ///< This is just because Sprite needs it
    MOVE_TIMEOUT_MS = 50, ///< Move function called every x ms
  };


  bool collisionDetected();

};

#endif // BONUS_H
