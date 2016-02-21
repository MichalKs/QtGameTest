#include <QApplication>
#include "game.h"

Game * game;

/**
 * @brief main
 * @param argc
 * @param argv
 * @return
 */
int main(int argc, char *argv[])
{
  QApplication a(argc, argv);

  game = new Game();
// show the view - it is invisible
  game->show();

  return a.exec();
}
