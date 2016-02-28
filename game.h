#ifndef GAME_H
#define GAME_H

#include <QGraphicsView>

class Player;
class QGraphicsScene;
class Score;
class Health;
class QSoundEffect;

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
  void enemyKilled(QGraphicsItem * casualty);
  void createBullet(int x, int y);
  void spawnEnemy();

private:
    QSoundEffect * effect;

};

#endif // GAME_H
