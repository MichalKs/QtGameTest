#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

class Game;
class QPushButton;
class QWidget;
class QHBoxLayout;
class QVBoxLayout;

class MainWindow: public QMainWindow {

    Q_OBJECT

public:
  MainWindow();
  ~MainWindow();

public slots:
  void createGame();

private:

  QWidget * centralWidget;
  QPushButton * newGameButton;
  QPushButton * quitButton;
  QHBoxLayout * hLayout1;
  QVBoxLayout * vLayout1;
  Game * game;
};

#endif // MAINWINDOW_H
