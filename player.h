#ifndef PLAYER_H
#define PLAYER_H

#include <QGraphicsPixmapItem>

class Player: public QObject, public QGraphicsPixmapItem {

  Q_OBJECT
public:

  Player(int initialHealth, QGraphicsItem * parent = 0);
  void keyPressEvent(QKeyEvent * event);

signals:
  void shoot(int x, int y);

private:
  static const int width  = 100;
  static const int height = 100;
  static const int speed = 10;
  int health;

};

#endif // PLAYER_H
