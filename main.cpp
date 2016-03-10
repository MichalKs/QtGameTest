#include <QApplication>
#include "game.h"
#include "mainwindow.h"

/*
 * TODO Decrease player health during impact
 * TODO Add main menu
 * TODO Add player die animation
 * TODO Add bonuses (additional health, better weapons)
 * TODO Add statusbar
 * TODO Add rescaling
 * TODO Add levels
 * TODO Add enemy missiles
 * TODO Add top score list
 *
 */

/**
 * @brief main
 * @param argc
 * @param argv
 * @return
 */
int main(int argc, char *argv[]) {
  QApplication a(argc, argv);

  MainWindow * window = new MainWindow();

  window->show();

  return a.exec();
}
