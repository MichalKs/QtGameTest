#ifndef ENEMY_H
#define ENEMY_H

#include <QGraphicsPixmapItem>

class Health;
class QTimer;

class Enemy: public QObject, public QGraphicsPixmapItem
{
  Q_OBJECT

public:
  Enemy(int initialHealth, QGraphicsItem * parent = NULL);
  ~Enemy();

  void die();
  void decreaseHealth();

public slots:
  void move();

private slots:
  void dieAnimation();

private:

  int health;
  static const int typesOfEnemies = 2;
  QTimer * timer;
  QTimer * explodeAnimationTimer;

};

#endif // ENEMY_H
