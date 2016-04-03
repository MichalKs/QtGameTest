#ifndef GAME_H
#define GAME_H

#include <QGraphicsView>

class GameScene;

/**
 * @brief The Game class This class is the widget responsible for displaying
 * the game scene.
 */
class Game: public QGraphicsView {
  Q_OBJECT

public:
  /**
   * @brief Game Default constructor of game view
   * @param parent The parent widget
   */
  Game(QWidget * parent = NULL);

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
  void resizeEvent(QResizeEvent * event);
  /**
   * @brief keyPressEvent Key press event
   * @param event Event
   */
  void keyPressEvent(QKeyEvent * event);
  /**
   * @brief mousePressEvent Mouse press event
   * @param event Event
   */
  void mousePressEvent(QMouseEvent * event);
  /**
   * @brief mouseMoveEvent Mouse move event
   * @param event Event
   */
  void mouseMoveEvent(QMouseEvent *event);

private:
  /**
   * @brief scene Scene of game (game logic) - it is displayed using this widget (the view)
   */
  GameScene * scene;

};

#endif // GAME_H
