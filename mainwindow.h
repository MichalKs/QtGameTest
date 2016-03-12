#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

class GameContainer;
class QPushButton;
class QWidget;
class QHBoxLayout;
class QVBoxLayout;
class QLabel;
class QStackedWidget;

class MainWindow: public QMainWindow {

    Q_OBJECT

public:
  MainWindow(QWidget * parent = 0);
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
  QStackedWidget * stackedWidget;

  QMenu * fileMenu;
  QMenu * aboutMenu;
  QMenu * extrasMenu;
  QMenu * optionsMenu;

  // actions
  QAction * newGameAction;
  QAction * loadGameAction;
  QAction * saveGameAction;
  QAction * exitAction;

  QAction * mouseMoveAction;
  QAction * audioToggleAction;

  QAction * topScoreAction;

  QAction * aboutAction;
  QAction * aboutQtAction;

  GameContainer * gameContainer;

};

#endif // MAINWINDOW_H
