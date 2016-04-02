#include "mainwindow.h"
#include "topscoresdialog.h"
#include "gamecontainer.h"
#include "gamescene.h"
#include "game.h"
#include "statusbar.h"
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
#include <QInputDialog>

MainWindow::MainWindow(QWidget * parent): QMainWindow(parent) {

  // all widgets will be reparented to QMainWindow when they are added to layout

  // stacked widget - shows main menu or game
  stackedWidget = new QStackedWidget();

  // create main menu widget
  mainMenuWidget = new QWidget();

  // create new game button
  newGameButton = new QPushButton("New game");
  connect(newGameButton, SIGNAL(clicked(bool)), this, SLOT(createGame()));

  // create quit button
  quitButton = new QPushButton("Quit game");
  connect(quitButton, SIGNAL(clicked(bool)), this, SLOT(close()));

  // wil be reparented (and hence deleted when necessary) when added to MainWindow layout
  QHBoxLayout * buttonLayout = new QHBoxLayout;
  QVBoxLayout * vLayout = new QVBoxLayout;

  // add buttons
  buttonLayout->addWidget(newGameButton);
  buttonLayout->addWidget(quitButton);

  // add background label
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

  // show the stacked widget as main widget
  setCentralWidget(stackedWidget);
  // set window icon
  setWindowIcon(QIcon(QPixmap(":/images/graphics/fighter/smallfighter0006.png")));
  // set window title
  setWindowTitle("Ugly Invaders From Space");
  // window has fixed size
  layout()->setSizeConstraint(QLayout::SetFixedSize);
  // create all user actions
  createActions();
  // create menus
  createMenus();
  // create statusbar
  statusBar();
  // read application settings once everything is created
  readSettings();

}

void MainWindow::createGame() {

  // once game is started there is no point starting it again
  newGameAction->setDisabled(true);
  newGameButton->setDisabled(true);
  toMainMenuAction->setEnabled(true);

  // create a new game
  gameContainer = new GameContainer();
  // scene has game logic, so we need it to connect GUI signals
  const GameScene * scene = gameContainer->getGame()->getGameScene();

  // connect various GUI options to game logic
  connect(pauseGameAction,    SIGNAL(toggled(bool)), scene, SLOT(pauseGame(bool)));
  connect(mouseMoveAction,    SIGNAL(toggled(bool)), scene, SLOT(mouseMoveEnable(bool)));
  connect(audioToggleAction,  SIGNAL(toggled(bool)), scene, SLOT(audioEnable(bool)));
  // if game finishes due to player death
  connect(scene, SIGNAL(finishGame()), this, SLOT(returnToMainMenu()));


  stackedWidget->addWidget(gameContainer);
  // change widget that is displayed
  emit changeWidget(1);

  statusBar()->showMessage("New game started", 2000);

}

void MainWindow::returnToMainMenu() {

  // get the score as int
  int currentScore = gameContainer->getStatusbar()->getScore();
  // destrou previous game
  delete gameContainer;
  // enable new game button
  newGameAction->setDisabled(false);
  newGameButton->setDisabled(false);
  toMainMenuAction->setEnabled(false);

  emit changeWidget(0);

  statusBar()->showMessage("Game finished", 2000);


  for (int i = 0; i < NUMBER_OF_SCORES; i++) {

    if (topScores.count() == i) {
      qDebug() << __FUNCTION__ << ": We found empty room in list";
      // if list is not complete we insert the score an end loop

      QString playerName = QInputDialog::getText(this, "Save score", "Enter name");
      if (playerName != "") {
        topScoreList.insert(i, playerName);
        topScores.insert(i, QString::number(currentScore));

        qDebug() << topScoreList;
        qDebug() << topScores;

      }
      break;
    } else if (topScores[i].toInt() < currentScore) {
      qDebug() << __FUNCTION__ << ": Score is better";

      QString playerName = QInputDialog::getText(this, "Save score", "Enter name");
      if (playerName != "") {

        // if the current score is bigger than the saved one
        // we insert the score before it
        topScores.insert(i, QString::number(currentScore));
        topScoreList.insert(i, playerName);
      }
      qDebug() << topScoreList;
      qDebug() << topScores;

      // if the list is too big remove last item
      if (topScores.count() > NUMBER_OF_SCORES) {
        topScores.removeLast();
        topScoreList.removeLast();


      }

      break;
    }
  }
}

void MainWindow::about() {

  QMessageBox::about(this, "About Ugly Invaders From Space",
                     "The game tells the tale of a horrible invasion of ugly aliens that "
                     "threaten humanity. In order to bring peace and aesthetics to the galaxy you must"
                     " murder them all without mercy :)"
                     "\nCreated in 2016");

}

void MainWindow::displayTopScorers() {

  TopScoresDialog tsd(topScoreList, topScores);
  tsd.exec();

}

void MainWindow::createActions() {

  // create actions
  newGameAction = new QAction("&New game", this);
  newGameAction->setShortcut(QKeySequence("Ctrl+N"));
  newGameAction->setStatusTip("Start a new game");
  newGameAction->setIcon(QIcon(":/images/graphics/icons/menu/newgame.png"));
  connect(newGameAction, SIGNAL(triggered(bool)), this, SLOT(createGame()));

  toMainMenuAction = new QAction("&Return to main menu", this);
  toMainMenuAction->setShortcut(QKeySequence("Ctrl+W"));
  toMainMenuAction->setStatusTip("Returns to main menu");
  toMainMenuAction->setEnabled(false);
  connect(toMainMenuAction, SIGNAL(triggered(bool)), this, SLOT(returnToMainMenu()));

  exitAction = new QAction("&Exit", this);
  exitAction->setStatusTip("Exit game");
  exitAction->setShortcut((QKeySequence("Ctrl+Q")));
  exitAction->setIcon(QIcon(":/images/graphics/icons/menu/exit.png"));
  connect(exitAction, SIGNAL(triggered(bool)), this, SLOT(close()));

  mouseMoveAction = new QAction("Enable &mouse movement", this);
  mouseMoveAction->setCheckable(true);
  mouseMoveAction->setStatusTip("Move player with mouse");

  audioToggleAction = new QAction("Enable &audio", this);
  audioToggleAction->setCheckable(true);
  audioToggleAction->setStatusTip("Mute all sounds");

  pauseGameAction = new QAction("&Pause game", this);
  pauseGameAction->setCheckable(true);
  pauseGameAction->setChecked(false);
  pauseGameAction->setStatusTip("Pause game");

  topScoreAction = new QAction("&Top scorers", this);
  topScoreAction->setStatusTip("Display top scorers");
  connect(topScoreAction, SIGNAL(triggered(bool)), this, SLOT(displayTopScorers()));

  aboutAction = new QAction("About", this);
  aboutAction->setStatusTip("Show info about game");
  connect(aboutAction, SIGNAL(triggered(bool)), this, SLOT(about()));

  aboutQtAction = new QAction("About &Qt", this);
  aboutQtAction->setStatusTip("Show info about Qt");
  connect(aboutQtAction, SIGNAL(triggered(bool)), qApp, SLOT(aboutQt()));
}

void MainWindow::createMenus() {

  // create menus
  fileMenu = menuBar()->addMenu("&File");
  fileMenu->addAction(newGameAction);
  fileMenu->addAction(toMainMenuAction);
  fileMenu->addAction(exitAction);

  optionsMenu = menuBar()->addMenu("&Options");
  optionsMenu->addAction(mouseMoveAction);
  optionsMenu->addAction(audioToggleAction);
  optionsMenu->addSeparator();
  optionsMenu->addAction(pauseGameAction);

  extrasMenu = menuBar()->addMenu("&Extras");
  extrasMenu->addAction(topScoreAction);

  helpMenu = menuBar()->addMenu("&Help");
  helpMenu->addAction(aboutAction);
  helpMenu->addAction(aboutQtAction);
}

void MainWindow::writeSettings() {
  QSettings settings("Ugly Invaders and Co.", "Ugly Invaders From Space");

  settings.setValue("geometry", geometry());
  settings.setValue("mouseMove", mouseMoveAction->isChecked());
  settings.setValue("audioOn", audioToggleAction->isChecked());
  settings.setValue("topScoreList", topScoreList);
  settings.setValue("topScore", topScores);
}

void MainWindow::readSettings() {
  QSettings settings("Ugly Invaders and Co.", "Ugly Invaders From Space");

  QRect rect = settings.value("geometry", QRect(200, 200, 640, 480)).toRect();
  move(rect.topLeft());
  resize(rect.size());

  bool mouseMove = settings.value("mouseMove", true).toBool();
  mouseMoveAction->setChecked(mouseMove);

  bool audioOn = settings.value("audioOn", true).toBool();
  audioToggleAction->setChecked(audioOn);

  topScoreList = settings.value("topScoreList", QStringList()).toStringList();
  topScores = settings.value("topScore", QStringList()).toStringList();

}

void MainWindow::closeEvent(QCloseEvent *event) {

  // message box asking if user wants to quit
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
