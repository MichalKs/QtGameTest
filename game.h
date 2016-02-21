#ifndef GAME_H
#define GAME_H

#include <QGraphicsView>

class Player;
class QGraphicsScene;
class Score;
class Health;

class Game: public QGraphicsView
{
public:
  Game(QWidget * parent = NULL);

public:
  QGraphicsScene * scene;
  Player * player;
  Score * score;
  Health * health;

};

#endif // GAME_H
