#ifndef STATUSBAR_H
#define STATUSBAR_H

#include <QWidget>

class QLabel;
class QProgressBar;

/**
 * @brief The Statusbar class shows and controls the status bar of the game
 */
class Statusbar: public QWidget {
  Q_OBJECT
public:
  /**
   * @brief Statusbar Constructor
   * @param parent Parent widget
   */
  Statusbar(QWidget * parent = 0);

  /**
   * @brief getScore Get the final score
   * @return Score
   */
  int getScore() {
    return score;
  }

public slots:
  /**
   * @brief increaseScore Increase score
   * @param increment Amount of increase
   */
  void increaseScore(int increment);
  /**
   * @brief changeHealth Update health
   * @param h New health value
   */
  void changeHealth(int h);

signals:
  /**
   * @brief healthUpdated Health was updated
   * @param health Health value
   */
  void healthUpdated(int health);

private:
  /**
   * @brief scoreLabel Shows the current score
   */
  QLabel * scoreLabel;
  /**
   * @brief healthLabel Shows the current health
   */
  QLabel * healthLabel;
  /**
   * @brief scoreIconLabel Icon for score
   */
  QLabel * scoreIconLabel;
  /**
   * @brief healthIconLabel Icon for health
   */
  QLabel * healthIconLabel;
  /**
   * @brief weaponLabel Label for weapon count
   */
  QLabel * weaponLabel;
  /**
   * @brief weaponIconLabel Icon for weapon
   */
  QLabel * weaponIconLabel;
  /**
   * @brief healthBar Progress bar for health
   */
  QProgressBar * healthBar;
  /**
   * @brief score Current score
   */
  int score;
};

#endif // STATUSBAR_H
