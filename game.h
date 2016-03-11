#ifndef GAME_H
#define GAME_H

#include <QGraphicsView>

class Player;
class QGraphicsScene;
class QSoundEffect;
class GameScene;

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

signals:
  void increaseScore(int increment);

private:
    QSoundEffect * effect;
    GameScene * scene;
    Player * player;

};

#endif // GAME_H
