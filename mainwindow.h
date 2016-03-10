#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

class Game;
class QPushButton;
class QWidget;
class QHBoxLayout;
class QVBoxLayout;
class QLabel;
class QStackedWidget;

class MainWindow: public QMainWindow {

    Q_OBJECT

public:
  MainWindow();
  ~MainWindow();

  void closeEvent(QCloseEvent * event);

public slots:
  void createGame();

signals:
  void changeWidget(int i);

private:

  QWidget * mainMenuWidget;
  QPushButton * newGameButton;
  QPushButton * quitButton;
  QLabel * backgroundLabel;

  QHBoxLayout * hLayout1;
  QVBoxLayout * vLayout1;
  Game * game;
  QStackedWidget * stackedWidget;

  QMenu * fileMenu;
  QMenu * aboutMenu;

  // actions
  QAction * newGameAction;
  QAction * loadGameAction;
  QAction * saveGameAction;
  QAction * exitAction;
  QAction * aboutAction;
  QAction * aboutQtAction;


};

#endif // MAINWINDOW_H
