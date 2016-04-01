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

  const GameScene* getGameScene() {
    return scene;
  }

  void resizeEvent(QResizeEvent * event);
  void keyPressEvent(QKeyEvent * event);
  void mousePressEvent(QMouseEvent * event);

private:
    GameScene * scene;
    Player * player;

};

#endif // GAME_H
