#ifndef ENEMY_H
#define ENEMY_H

#include <QGraphicsItem>
#include <QObject>

class Enemy : public QObject, public QGraphicsRectItem
{
  Q_OBJECT

public:
  Enemy();
  ~Enemy();

public slots:
  void move();

};

#endif // ENEMY_H
