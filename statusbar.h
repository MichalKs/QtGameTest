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
   * @brief Statusbar
   * @param initialhealth Initial health displayed on the statusbar
   * @param initialMissiles Initial number of missiles displayed on the status bar
   * @param parent Parent widget
   */
  Statusbar(int initialhealth, int initialMissiles, QWidget * parent = 0);
  /**
   * @brief getScore Get the final score
   * @return Score
   */
  int getScore() const {
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
  /**
   * @brief changeMissileCount Change missile count
   */
  void changeMissileCount(int c);

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
   * @brief score Current score
   */
  int score;
  /**
   * @brief missileCount Missile count
   */
  int missileCount;
  /**
   * @brief health Player health
   */
  int health;
};

#endif // STATUSBAR_H
