#include "gamecontainer.h"
#include "game.h"
#include "statusbar.h"
#include <QVBoxLayout>
#include "gamescene.h"

GameContainer::GameContainer(QWidget *parent): QWidget(parent) {

  // create a game view
  game = new Game();
  // get the pointer to the scene (needed to connet menu actions to game slots)
  const GameScene * scene = game->getGameScene();

  statusbar = new Statusbar();
  QVBoxLayout * layout = new QVBoxLayout();

  // connect any signals and slots between game and status bar here
  // increasing score
  connect(scene, SIGNAL(increaseScore(int)), statusbar, SLOT(increaseScore(int)));
  // changing health
  connect(scene, SIGNAL(playerHealthChanged(int)), statusbar, SLOT(changeHealth(int)));

  layout->addWidget(game);
  layout->addWidget(statusbar);

  setLayout(layout);
}
