#ifndef GAME_H
#define GAME_H

#include <QGraphicsView>

class Player;
class QGraphicsScene;
class Score;
class QSoundEffect;

class Game: public QGraphicsView {
  Q_OBJECT

public:
  Game(QWidget * parent = NULL);

  void resizeEvent(QResizeEvent * event);
  void keyPressEvent(QKeyEvent * event);
  void mousePressEvent(QMouseEvent * event);

public slots:
  void enemyKilled(QGraphicsItem * casualty);
  void createBullet(int x, int y);
  void spawnEnemy();

private:
    QSoundEffect * effect;
    QGraphicsScene * scene;
    Player * player;
    Score * score;
};

#endif // GAME_H
