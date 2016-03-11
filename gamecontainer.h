#ifndef GAMECONTAINER_H
#define GAMECONTAINER_H

#include <QWidget>

class QVBoxLayout;
class Game;
class Statusbar;

class GameContainer: public QWidget {
public:
  GameContainer();

private:
  Game * game;
  Statusbar * statusbar;
  QVBoxLayout * layout;
};

#endif // GAMECONTAINER_H
