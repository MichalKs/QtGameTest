#ifndef ENEMY_H
#define ENEMY_H

#include <QGraphicsPixmapItem>

class Health;

class Enemy: public QObject, public QGraphicsPixmapItem
{
  Q_OBJECT

public:
  Enemy(int initialHealth, QGraphicsItem * parent = NULL);

  void die();
  void decreaseHealth();

public slots:
  void move();

private:

  int health;

};

#endif // ENEMY_H
