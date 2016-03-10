
#include "mainwindow.h"
#include "game.h"
#include <QPushButton>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QWidget>

MainWindow::MainWindow() {

  // create main widget
  centralWidget = new QWidget();
  newGameButton = new QPushButton("New game");
  connect(newGameButton,SIGNAL(clicked(bool)), this, SLOT(createGame()));

  quitButton = new QPushButton("Quit game");
  connect(quitButton, SIGNAL(clicked(bool)), this, SLOT(close()));

  hLayout1 = new QHBoxLayout;
  vLayout1 = new QVBoxLayout;

  hLayout1->addWidget(newGameButton);
  hLayout1->addWidget(quitButton);

  vLayout1->addLayout(hLayout1);

  centralWidget->setLayout(vLayout1);

  setCentralWidget(centralWidget);


}

void MainWindow::createGame() {

  // create a new game
  game = new Game();
  vLayout1->addWidget(game);
  newGameButton->setDisabled(true);

  // set game as central widget
//  setCentralWidget(game);

}

MainWindow::~MainWindow() {

}
