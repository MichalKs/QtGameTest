#include "gamecontainer.h"
#include "game.h"
#include "statusbar.h"
#include <QVBoxLayout>
#include "gamescene.h"

GameContainer::GameContainer(QWidget *parent): QWidget(parent) {

  game = new Game();
  const GameScene * scene = game->getGameScene();

  statusbar = new Statusbar();
  QVBoxLayout * layout = new QVBoxLayout();

  // connect any signals and slots between game and status bar here
  connect(scene, SIGNAL(increaseScore(int)), statusbar, SLOT(increaseScore(int)));
  connect(scene, SIGNAL(playerHealthChanged(int)), statusbar, SLOT(changeHealth(int)));


  layout->addWidget(game);
  layout->addWidget(statusbar);

  setLayout(layout);
}
