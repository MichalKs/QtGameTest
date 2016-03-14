#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

class GameContainer;
class QPushButton;
class QLabel;
class QStackedWidget;

/**
 * @brief The MainWindow class Main window for the application (it displays main menu or
 * the game scene if the game is started).
 */
class MainWindow: public QMainWindow {

    Q_OBJECT

public:
  /**
   * @brief MainWindow Constructor for main window
   * @param parent Parent widget
   */
  MainWindow(QWidget * parent = 0);
  ~MainWindow();

  /**
   * @brief closeEvent Reimplementation of close event to ask the player
   * if he really wants to quit.
   * @param event Close event
   */
  void closeEvent(QCloseEvent * event);

  QStringList& getTopScoreList();

public slots:
  /**
   * @brief createGame Slot for creating game (New game action triggered)
   */
  void createGame();
  /**
   * @brief about Displays a dialog with info about the game
   */
  void about();
  /**
   * @brief displayTopScorers Displays a dialog with the list of top scores
   */
  void displayTopScorers();

signals:
  /**
   * @brief changeWidget Signal emmited when a change of the displayed widget is needed
   * (a QStackWidget is used as the main widget).
   * @param i Number of widget to display (starting from zero)
   */
  void changeWidget(int i);

private:

  /**
   * @brief writeSettings Write application settings to OS (registry or file)
   */
  void writeSettings();
  /**
   * @brief readSettings Read application settings from OS (registry or file)
   */
  void readSettings();

  QStringList topScoreList;

  /**
   * @brief stackedWidget The stacked widget display the main menu widget or the
   * game container
   */
  QStackedWidget  * stackedWidget;
  QWidget         * mainMenuWidget;
  /**
   * @brief gameContainer Game container contains the game view and the status bar of the game
   */
  GameContainer   * gameContainer;
  /**
   * @brief newGameButton Start a new game
   */
  QPushButton     * newGameButton;
  /**
   * @brief quitButton Quit game
   */
  QPushButton     * quitButton;
  /**
   * @brief backgroundLabel background image for main menu
   */
  QLabel          * backgroundLabel;

  // menus
  QMenu * fileMenu;
  QMenu * helpMenu;
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

};

#endif // MAINWINDOW_H
