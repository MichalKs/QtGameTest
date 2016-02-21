#ifndef ENEMY_H
#define ENEMY_H

#include <QGraphicsItem>
#include <QObject>
#include <QGraphicsRectItem>

class Enemy : public QObject, public QGraphicsRectItem
{
  Q_OBJECT

public:
  Enemy(QGraphicsItem * parent = 0);

public slots:
  void move();

};

#endif // ENEMY_H
