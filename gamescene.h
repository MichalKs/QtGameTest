#ifndef GAMESCENE_H
#define GAMESCENE_H

#include <QGraphicsScene>
#include <QList>
#include "sprite.h"

class QSoundEffect;
class Player;

class GameScene: public QGraphicsScene {

  Q_OBJECT
public:

  GameScene(QObject * parent = 0);

  bool event(QEvent * event);
  void mousePressEvent(QGraphicsSceneMouseEvent * mouseEvent);
  void keyPressEvent(QKeyEvent * event);
  void mouseMoveEvent(QGraphicsSceneMouseEvent * mouseEvent);
  void addItem(QGraphicsItem *item);
  void removeItem(QGraphicsItem *item);

public slots:
  void enemyKilled(QGraphicsItem * casualty);
  void createBullet(int x, int y);
  void spawnEnemy();
  void pauseGame(bool isPaused);
  void playerHealthDecreased(int h);

  void mouseMoveEnable(bool enable) {
    mouseMoveEnabled = enable;
  }

  void audioEnable(bool enable) {
    audioEnabled = enable;
  }

signals:
  void increaseScore(int increment);
  void playerHealthChanged(int h);

private:
  Player * player;
  QSoundEffect * effect;
  QList<Sprite*> * spriteList;
  bool gamePaused;
  bool mouseMoveEnabled;
  bool audioEnabled;

};

#endif // GAMESCENE_H
