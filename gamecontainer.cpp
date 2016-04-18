#include "gamecontainer.h"
#include "game.h"
#include "statusbar.h"
#include "gamescene.h"
#include "player.h"
#include <QVBoxLayout>

GameContainer::GameContainer(QWidget *parent): QWidget(parent) {

  // create a game view
  game = new Game();
  // get the pointer to the scene (needed to connet menu actions to game slots)
  GameScene * scene = game->getGameScene();

  statusbar = new Statusbar(scene->getPlayer()->getHealth(),
                            scene->getPlayer()->getMissileCount());
  QVBoxLayout * layout = new QVBoxLayout();

  // connect any signals and slots between game and status bar here
  // increasing score
  connect(scene, SIGNAL(increaseScore(int)), statusbar, SLOT(increaseScore(int)));
  // changing health
  connect(scene, SIGNAL(playerHealthChanged(int)), statusbar, SLOT(changeHealth(int)));
  // decrease bullet count
  connect(scene, SIGNAL(changeMissileCount(int)), statusbar, SLOT(changeMissileCount(int)));

  // set proportions between game and statusbar

  QSizePolicy spSb = statusbar->sizePolicy();
  spSb.setVerticalStretch(1);
  statusbar->setSizePolicy(spSb);

  QSizePolicy spGm = game->sizePolicy();
  spGm.setVerticalStretch(10);
  game->setSizePolicy(spGm);

  layout->addWidget(game);
  layout->addWidget(statusbar);


  setLayout(layout);
}
