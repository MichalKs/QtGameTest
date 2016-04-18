#ifndef GAME_H
#define GAME_H

#include <QGraphicsView>
#include "gamescene.h"

/**
 * @brief The Game class This class is the widget responsible for displaying
 * the game scene - it is the view.
 */
class Game: public QGraphicsView {

  Q_OBJECT

public:
  /**
   * @brief Game Default constructor of game view
   * @param parent The parent widget
   */
  Game(QWidget * parent = 0);
  /**
   * @brief getGameScene Returns the scene of the game
   * @return Scene of the game
   */
  GameScene * getGameScene() {
    return scene;
  }
  /**
   * @brief resizeEvent Resize event
   * @param event Event
   */
  void resizeEvent(QResizeEvent * event) {
    fitInView(0, 0, GameScene::SCENE_WIDTH, GameScene::SCENE_HEIGHT);
    QGraphicsView::resizeEvent(event);
  }

private:
  /**
   * @brief scene Scene of game (game logic) - it is displayed using this widget (the view)
   */
  GameScene * scene;

};

#endif // GAME_H
