#include "gamecontainer.h"
#include <QVBoxLayout>
#include "game.h"
#include "statusbar.h"

GameContainer::GameContainer() {

  game = new Game();
  statusbar = new Statusbar();
  layout = new QVBoxLayout();

  connect(game, SIGNAL(increaseScore(int)), statusbar, SLOT(increaseScore(int)));

  layout->addWidget(game);
  layout->addWidget(statusbar);

  setLayout(layout);

}
