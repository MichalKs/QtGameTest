#ifndef GAME_H
#define GAME_H

#include <QGraphicsView>

class Player;
class QGraphicsScene;
class Score;
class Health;

class Game: public QGraphicsView
{
  Q_OBJECT

public:
  Game(QWidget * parent = NULL);

  QGraphicsScene * scene;
  Player * player;
  Score * score;
  Health * health;

public slots:
  void enemyKilled();

};

#endif // GAME_H
