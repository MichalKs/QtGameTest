#include <QApplication>
#include "game.h"

/**
 * @brief main
 * @param argc
 * @param argv
 * @return
 */
int main(int argc, char *argv[]) {
  QApplication a(argc, argv);

  Game * game = new Game();
  // show the game
  game->show();

  return a.exec();
}
