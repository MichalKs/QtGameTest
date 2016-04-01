#ifndef GAMECONTAINER_H
#define GAMECONTAINER_H

#include <QWidget>

class Game;
class Statusbar;

/**
 * @brief The GameContainer class The GameContainer class serves as only a container for
 * the game widget and the status bar widget.
 */
class GameContainer: public QWidget {

public:
  /**
   * @brief GameContainer Constructor for game container
   * @param parent Parent widget
   */
  GameContainer(QWidget * parent = 0);

  Game * getGame() {
    return game;
  }

private:
  /**
   * @brief game Game view
   */
  Game * game;
  /**
   * @brief statusbar Status bar widget
   */
  Statusbar * statusbar;
};

#endif // GAMECONTAINER_H
