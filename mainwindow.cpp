
#include "mainwindow.h"
#include "topscoresdialog.h"
#include "gamecontainer.h"
#include <QDebug>
#include <QPushButton>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QWidget>
#include <QLabel>
#include <QStackedWidget>
#include <QMenuBar>
#include <QApplication>
#include <QMessageBox>
#include <QCloseEvent>
#include <QStatusBar>
#include <QSettings>

MainWindow::MainWindow(QWidget * parent): QMainWindow(parent) {

  // stacked widget - show main menu or game
  stackedWidget = new QStackedWidget();

  // create main menu widget
  mainMenuWidget = new QWidget();

  // create new game button
  newGameButton = new QPushButton("New game");
  connect(newGameButton,SIGNAL(clicked(bool)), this, SLOT(createGame()));

  // create quit button
  quitButton = new QPushButton("Quit game");
  connect(quitButton, SIGNAL(clicked(bool)), this, SLOT(close()));


  // wil be reparented when added to MainWindow layout
  QHBoxLayout * buttonLayout = new QHBoxLayout;
  QVBoxLayout * vLayout = new QVBoxLayout;

  // add buttons
  buttonLayout->addWidget(newGameButton);
  buttonLayout->addWidget(quitButton);

  // add backgroung
  backgroundLabel = new QLabel();
  backgroundLabel->setPixmap(
        QPixmap(":/images/graphics/background/science-fiction-441708_960_720.jpg").
        scaled(640, 480, Qt::KeepAspectRatio));

  // add buttons and label
  vLayout->addWidget(backgroundLabel);
  vLayout->addLayout(buttonLayout);

  // set main layout
  mainMenuWidget->setLayout(vLayout);

  // add main menu widget to stack
  stackedWidget->addWidget(mainMenuWidget);

  connect(this, SIGNAL(changeWidget(int)), stackedWidget, SLOT(setCurrentIndex(int)));

  setCentralWidget(stackedWidget);

  setWindowIcon(QIcon(QPixmap(":/images/graphics/fighter/smallfighter0006.png")));
  setWindowTitle("Ugly Invaders From Space");
  layout()->setSizeConstraint(QLayout::SetFixedSize);

  // create actions
  newGameAction = new QAction("&New game", this);
  newGameAction->setShortcut(QKeySequence("Ctrl+N"));
  newGameAction->setStatusTip("Start a new game");
  newGameAction->setIcon(QIcon(":/images/graphics/icons/menu/newgame.png"));
  connect(newGameAction, SIGNAL(triggered(bool)), this, SLOT(createGame()));

  exitAction = new QAction("&Exit", this);
  exitAction->setStatusTip("Exit game");
  exitAction->setShortcut((QKeySequence("Ctrl+Q")));
  exitAction->setIcon(QIcon(":/images/graphics/icons/menu/exit.png"));
  connect(exitAction, SIGNAL(triggered(bool)), this, SLOT(close()));

  mouseMoveAction = new QAction("Enable &mouse movement", this);
  mouseMoveAction->setCheckable(true);
  mouseMoveAction->setChecked(true);
  mouseMoveAction->setStatusTip("Move player with mouse");
  //connect(mouseMoveAction, SIGNAL(toggled(bool)), game, SLOT()

  audioToggleAction = new QAction("Enable &audio", this);
  audioToggleAction->setCheckable(true);
  audioToggleAction->setChecked(true);
  audioToggleAction->setStatusTip("Mute all sounds");

  topScoreAction = new QAction("&Top scorers", this);
  topScoreAction->setStatusTip("Display top scorers");
  connect(topScoreAction, SIGNAL(triggered(bool)), this, SLOT(displayTopScorers()));

  aboutAction = new QAction("About", this);
  aboutAction->setStatusTip("Show info about game");
  connect(aboutAction, SIGNAL(triggered(bool)), this, SLOT(about()));

  aboutQtAction = new QAction("About &Qt", this);
  aboutQtAction->setStatusTip("Show info about Qt");
  connect(aboutQtAction, SIGNAL(triggered(bool)), qApp, SLOT(aboutQt()));


  // create menus

  fileMenu = menuBar()->addMenu("&File");
  fileMenu->addAction(newGameAction);
  fileMenu->addAction(exitAction);

  optionsMenu = menuBar()->addMenu("&Options");
  optionsMenu->addAction(mouseMoveAction);
  optionsMenu->addSeparator();
  optionsMenu->addAction(audioToggleAction);

  extrasMenu = menuBar()->addMenu("&Extras");
  extrasMenu->addAction(topScoreAction);

  helpMenu = menuBar()->addMenu("&Help");
  helpMenu->addAction(aboutAction);
  helpMenu->addAction(aboutQtAction);

  // create statusbar
  statusBar();

  readSettings();

}

void MainWindow::createGame() {

  newGameAction->setDisabled(true);

  // create a new game
  gameContainer = new GameContainer();
//  backgroundLabel->hide();
//  vLayout1->removeWidget(backgroundLabel);

  stackedWidget->addWidget(gameContainer);
  emit changeWidget(1);

  newGameButton->setDisabled(true);
  statusBar()->showMessage("New game started", 2000);
//  resize(800, 600);

  // set game as central widget
//  setCentralWidget(game);

}

void MainWindow::about() {

  QMessageBox::about(this, "About Ugly Invaders From Space",
                     "The game tells the tale of a horrible invasion of ugly aliens that "
                     "threaten humanity. In order to bring peace and aesthetics to the galaxy you must"
                     " murder them all without mercy :)"
                     "\nCreated in 2016");

}

void MainWindow::displayTopScorers() {

  TopScoresDialog tsd;
  tsd.exec();

}

void MainWindow::writeSettings() {
  QSettings settings("Ugly Invaders and Co.", "Ugly Invaders From Space");

  settings.setValue("geometry", geometry());
  settings.setValue("mouseMove", mouseMoveAction->isChecked());
  settings.setValue("audioOn", audioToggleAction->isChecked());
}

void MainWindow::readSettings() {
  QSettings settings("Ugly Invaders and Co.", "Ugly Invaders From Space");

  QRect rect = settings.value("geometry", QRect(200, 200, 640, 480)).toRect();
  move(rect.topLeft());
  resize(rect.size());

  bool mouseMove = settings.value("mouseMove", true).toBool();
  mouseMoveAction->setChecked(mouseMove);

  bool audioOn = settings.value("audioOn", true).toBool();
  audioToggleAction->setChecked(mouseMove);
}

MainWindow::~MainWindow() {

}

void MainWindow::closeEvent(QCloseEvent *event) {

  // add message box here asking if user wants to quit

  int r = QMessageBox::question(this, "Ugly Invaders From Space",
                        "Are you sure you want to quit?",
                        QMessageBox::Yes | QMessageBox::Default,
                        QMessageBox::Cancel | QMessageBox::Escape);
  if (r == QMessageBox::Yes) {
    qDebug() << "Closing game";
    writeSettings();
    event->accept();
  } else {
    event->ignore();
    statusBar()->showMessage("Exit cancelled", 2000);
  }

}
