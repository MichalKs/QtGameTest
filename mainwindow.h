#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

class GameContainer;
class QPushButton;
class QLabel;
class QStackedWidget;
class BackgroundLabel;

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

  /**
   * @brief closeEvent Reimplementation of close event to ask the player
   * if he really wants to quit.
   * @param event Close event
   */
  void closeEvent(QCloseEvent * event);

  /**
   * @brief getTopScoreList Gets the top score list
   * @return QStringList of top scorers
   */
  QStringList& getTopScoreList() {
    return topScoreList;
  }

public slots:

  /**
   * @brief createGame Slot for creating game (New game action triggered)
   */
  void createGame();

  /**
   * @brief returnToMainMenu Returns to main menu once game is started
   */
  void returnToMainMenu();

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
   * @details There will probably be only two stacked widgets - the main menu and the gameContainer
   * @param i Number of widget to display (starting from zero)
   */
  void changeWidget(int i);

private:

  enum {
    NUMBER_OF_SCORES = 10,
  };

  /**
   * @brief createActions Create all GUI actions
   */
  void createActions();

  /**
   * @brief createMenus Create all menu bars
   */
  void createMenus();

  /**
   * @brief writeSettings Write application settings to OS (registry or file)
   */
  void writeSettings();

  /**
   * @brief readSettings Read application settings from OS (registry or file)
   */
  void readSettings();

  /**
   * @brief topScoreList List of top scorers (names)
   */
  QStringList topScoreList;
  /**
   * @brief topScores List of top scores (numerical values as strings)
   */
  QStringList  topScores;

  /**
   * @brief stackedWidget The stacked widget displays the main menu widget or the
   * game container
   */
  QStackedWidget  * stackedWidget;

  /**
   * @brief mainMenuWidget Widget with main menu
   */
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
  BackgroundLabel * backgroundLabel;

  // menus
  QMenu * fileMenu;     ///< File menu
  QMenu * helpMenu;     ///< Help menu
  QMenu * extrasMenu;   ///< Extra features menu
  QMenu * optionsMenu;  ///< Options menu

  // actions
  QAction * newGameAction;    ///< Starts a new game
  QAction * toMainMenuAction; ///< Returns to main menu
  QAction * exitAction;       ///< Exit program
  QAction * mouseMoveAction;  ///< Enable/disable mouse movement of player
  QAction * audioToggleAction;///< Enable/disable audio
  QAction * pauseGameAction;  ///< Pause/unpasue game
  QAction * topScoreAction;   ///< Display top scorers list
  QAction * aboutAction;      ///< Display dialog with info about game
  QAction * aboutQtAction;    ///< Display dialog with info about Qt

};

#endif // MAINWINDOW_H
