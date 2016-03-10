#ifndef GAMESCENE_H
#define GAMESCENE_H

#include <QGraphicsScene>
#include "player.h"

class GameScene: public QGraphicsScene {

public:

  GameScene(Player * player);

  bool event(QEvent * event);
  void mousePressEvent(QGraphicsSceneMouseEvent * mouseEvent);
  void mouseMoveEvent(QGraphicsSceneMouseEvent * mouseEvent);
  void addItem(QGraphicsItem *item);

private:
  Player * playerPtr;
};

#endif // GAMESCENE_H
