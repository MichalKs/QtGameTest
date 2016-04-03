#include <QApplication>
#include <QSplashScreen>
#include "mainwindow.h"

/*
 * TODO Add player die animation
 * TODO Add bonuses (additional health, better weapons)
 * TODO Add rescaling
 * TODO Add levels
 * TODO Add enemy missiles
 */

/**
 * @brief main
 * @param argc
 * @param argv
 * @return
 */
int main(int argc, char *argv[]) {
  QApplication app(argc, argv);

  enum {
    SPLASH_WIDTH = 640,
    SPLASH_HEIGHT = 480,
  };

  // test splash screen functionality
  QSplashScreen * splash = new QSplashScreen;
  // set pixmpa for splash
  splash->setPixmap(
        QPixmap(":/images/graphics/background/science-fiction-441708_960_720.jpg").
        scaled(SPLASH_WIDTH, SPLASH_HEIGHT, Qt::KeepAspectRatio));
  splash->show();
  // show message on splash screen
  splash->showMessage("Loading graphics...",
                      Qt::AlignRight | Qt::AlignTop, Qt::white);

  // emulate loading graphics
  for (long long i = 500000L; i > 0; i--) {
    app.processEvents();
  }

  // create main window
  MainWindow * window = new MainWindow();

  // show message on splash screen
  splash->showMessage("Setting up the main window...",
                      Qt::AlignRight | Qt::AlignTop, Qt::white);

  // emulate setting up main window
  for (long long i = 500000L; i > 0; i--) {
    app.processEvents();
  }

  // show main window of program
  window->show();

  // delete splash
  splash->finish(window);
  delete splash;

  return app.exec();
}
