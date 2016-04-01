#include <QApplication>
#include <QSplashScreen>
#include "mainwindow.h"

/*
 * TODO Add player die animation
 * TODO Add missile counting
 * TODO Add bonuses (additional health, better weapons)
 * TODO Add rescaling
 * TODO Add levels
 * TODO Add enemy missiles
 * TODO Add top score list (reading file)
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

//  QSplashScreen * splash = new QSplashScreen;
//  splash->setPixmap(
//        QPixmap(":/images/graphics/background/science-fiction-441708_960_720.jpg").
//        scaled(640, 480, Qt::KeepAspectRatio));
//  splash->show();
  //splash->showMessage("Loading graphics...",
                      //Qt::AlignRight | Qt::AlignTop, Qt::white);

//  for (int i = 1000000000; i > 0; i--) {

//  }

  MainWindow * window = new MainWindow();

  //splash->showMessage("Setting up the main window...",
               //       Qt::AlignRight | Qt::AlignTop, Qt::white);

//  for (int i = 1000000000; i > 0; i--) {

//  }

  window->show();
//  splash->finish(window);
//  delete splash;

  return a.exec();
}
