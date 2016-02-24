#ifndef BULLET_H
#define BULLET_H

#include <QGraphicsPixmapItem>
#include <QObject>

class Bullet : public QObject, public QGraphicsPixmapItem
{
  Q_OBJECT
public:
  Bullet(QGraphicsItem *parent = 0);

public slots:
  void move();

signals:
  void enemyKilled();

private:
  static const int width = 100;
  static const int height = 100;
  static const int moveTimeoutMs = 50;
  static const int speed = 10;

};

#endif // BULLET_H
