
#include "mainwindow.h"
#include "game.h"
#include <QDebug>
#include <QPushButton>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QWidget>
#include <QLabel>
#include <QStackedWidget>
#include <QMenuBar>
#include <QApplication>

MainWindow::MainWindow() {


  stackedWidget = new QStackedWidget();

  // create main menu widget
  mainMenuWidget = new QWidget();
  newGameButton = new QPushButton("New game");
  connect(newGameButton,SIGNAL(clicked(bool)), this, SLOT(createGame()));

  quitButton = new QPushButton("Quit game");
  connect(quitButton, SIGNAL(clicked(bool)), this, SLOT(close()));

  hLayout1 = new QHBoxLayout;
  vLayout1 = new QVBoxLayout;

  hLayout1->addWidget(newGameButton);
  hLayout1->addWidget(quitButton);

  backgroundLabel = new QLabel();
  backgroundLabel->setPixmap(
        QPixmap(":/images/graphics/background/science-fiction-441708_960_720.jpg").
        scaled(640, 480, Qt::KeepAspectRatio));

  vLayout1->addWidget(backgroundLabel);

  vLayout1->addLayout(hLayout1);

  mainMenuWidget->setLayout(vLayout1);

  stackedWidget->addWidget(mainMenuWidget);

  connect(this,SIGNAL(changeWidget(int)), stackedWidget, SLOT(setCurrentIndex(int)));

  setCentralWidget(stackedWidget);


  setWindowIcon(QIcon(QPixmap(":/images/graphics/fighter/smallfighter0006.png")));


  newGameAction = new QAction("&New game", this);
//  newGameAction->setShortcut("Ctrl+N");
  newGameAction->setStatusTip("Start a new game");
  connect(newGameAction, SIGNAL(triggered(bool)), this, SLOT(createGame()));

  exitAction = new QAction("&Exit", this);
  exitAction->setStatusTip("Exit game");
  connect(exitAction, SIGNAL(triggered(bool)), this, SLOT(close()));

  aboutQtAction = new QAction("About &Qt", this);
  aboutQtAction->setStatusTip("Show info about Qt");
  connect(aboutQtAction, SIGNAL(triggered(bool)), qApp, SLOT(aboutQt()));

  fileMenu = menuBar()->addMenu("&File");
  fileMenu->addAction(newGameAction);
  fileMenu->addAction(exitAction);

  aboutMenu = menuBar()->addMenu("&About");
  aboutMenu->addAction(aboutQtAction);


}

void MainWindow::createGame() {

  // create a new game
  game = new Game();
//  backgroundLabel->hide();
//  vLayout1->removeWidget(backgroundLabel);

  stackedWidget->addWidget(game);
  emit changeWidget(1);

  newGameButton->setDisabled(true);
//  resize(800, 600);

  // set game as central widget
//  setCentralWidget(game);

}

MainWindow::~MainWindow() {

}

void MainWindow::closeEvent(QCloseEvent *event) {

  qDebug() << "Closing game";
  QMainWindow::closeEvent(event);

}
