#include "gamecontainer.h"
#include "game.h"
#include "statusbar.h"
#include <QVBoxLayout>

GameContainer::GameContainer(QWidget *parent): QWidget(parent) {

  game = new Game();
  statusbar = new Statusbar();
  QVBoxLayout * layout = new QVBoxLayout();

  // connect any signals and slots between game and status bar here
  connect(game, SIGNAL(increaseScore(int)), statusbar, SLOT(increaseScore(int)));

  layout->addWidget(game);
  layout->addWidget(statusbar);

  setLayout(layout);
}
