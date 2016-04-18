#ifndef GAMESCENE_H
#define GAMESCENE_H

#include <QGraphicsScene>
#include <QSoundEffect>
#include <QTimer>
#include "player.h"

class Sprite;

/**
 * @brief The GameScene class contains the logic of the game - it interconnects
 * the player with the enemy and the bullets, is responsible for creating enemies
 * and bullets.
 */
class GameScene: public QGraphicsScene {

  Q_OBJECT

public:
  /**
   * @brief GameScene Constructor for game widget
   * @param parent The parent object
   */
  GameScene(QObject * parent = 0);

  ~GameScene() {
    delete spriteList;
  }

  /**
   * @brief mousePressEvent Mouse press event
   * @param mouseEvent Mouse press event
   */
  void mousePressEvent(QGraphicsSceneMouseEvent * mouseEvent) {

    if (!gamePaused && mouseMoveEnabled) {
      player->mousePressEvent(mouseEvent);
    }

  }
  /**
   * @brief mouseMoveEvent Mouse move event
   * @param mouseEvent Mouse move event
   */
  void mouseMoveEvent(QGraphicsSceneMouseEvent * mouseEvent) {
    if (!gamePaused && mouseMoveEnabled) {
      player->mouseMoveEvent(mouseEvent);
    }
  }
  /**
   * @brief keyPressEvent Key press event
   * @param event Key press event
   */
  void keyPressEvent(QKeyEvent * event) {
    if (!gamePaused) {
      // change focus to player to get keyboard events
      player->setFocus();
      // this will pass event to focus item
      QGraphicsScene::keyPressEvent(event);
    }
  }
  /**
   * @brief addItem Adds item to scene
   * @param item The added item
   */
  void addItem(QGraphicsItem *item);
  /**
   * @brief removeItem Removes item from scene
   * @param item Removed item
   */
  void removeItem(QGraphicsItem *item);
  /**
   * @brief getPlayer Gets the player object
   * @return Player object
   */
  Player * getPlayer() {
    return player;
  }

  /**
   * @brief Public constants
   */
  enum {
    SCENE_WIDTH = 800,          ///< Scene widht
    SCENE_HEIGHT = 600,         ///< Scene height
  };

public slots:
  /**
   * @brief enemyKilled Enemy killed slot (called whenever an enemy is hit)
   * @param casualty The graphic item that represents the enemy
   */
  void enemyKilled(QGraphicsItem * casualty);
  /**
   * @brief createBullet Crete bullet slot (called whenever player shoots)
   * @param x X position of new bullet
   * @param y Y position of new bullet
   */
  void createBullet(int x, int y);
  /**
   * @brief fireEmptyGun When we run out of bullets this function plays a
   * sound of an empty gun
   */
  void fireEmptyGun() {

    const float soundVolume = 0.5f;
    // play empty gun click sound if audio is enabled
    if (audioEnabled) {
      effect->setSource(QUrl("qrc:/sounds/sounds/empty-gun-shot.wav"));
      effect->setVolume(soundVolume);
      effect->play();
    }
  }
  /**
   * @brief spawnEnemy Called periodically to create new enemies
   */
  void spawnEnemy();
  /**
   * @brief spawnBonuses Called periodically to create bonuses
   */
  void spawnBonuses();
  /**
   * @brief pauseGame Pause game slot - stops player and enemies
   * @param isPaused true - pause game, false - unpause game
   */
  void pauseGame(bool isPaused);
  /**
   * @brief playerHealthDecreased Slot called when player's health gets decreased
   * @param h New health value
   */
  void playerHealthDecreased(int h) {
    // inform the statusbar that player health changed
    emit playerHealthChanged(h);
  }
  /**
   * @brief playerMissileCountChanged Inform status bar that number of
   * missiles of player changed
   * @param c New missile count
   */
  void playerMissileCountChanged(int c) {
    emit changeMissileCount(c);
  }
  /**
   * @brief playerDied Slot called when player dies (health decreases to 0)
   */
  void playerDied() {
    // inform main window that game is to be deleted
    emit finishGame();
  }
  /**
   * @brief mouseMoveEnable Enables/disables mouse movement for player
   * @param enable true - enables mouse, false - disables mouse
   */
  void mouseMoveEnable(bool enable) {
    mouseMoveEnabled = enable;
  }
  /**
   * @brief audioEnable Enables/disables audio
   * @param enable true - enable audio, false - disable audio
   */
  void audioEnable(bool enable) {
    audioEnabled = enable;
  }
  /**
   * @brief increaseDifficulty increses the game difficulty
   * @details It is called periodically as the game progresses
   */
  void increaseDifficulty();

signals:
  /**
   * @brief increaseScore Signal for informing statusbar that score is incremented
   * @param increment The value by which score is incremented
   */
  void increaseScore(int increment);
  /**
   * @brief playerHealthChanged Signal to inform the statubar that the health of the
   * player is changed.
   * @param h Change in health
   */
  void playerHealthChanged(int h);
  /**
   * @brief finishGame Signal to inform the main windows that the game is to be
   * deleted, because player died.
   */
  void finishGame();
  /**
   * @brief changeMissileCount Change missile count on status bar
   */
  void changeMissileCount(int c);

private:
  /**
   * @brief Private constants
   */
  enum {
    PLAYER_DEFAULT_SPEED  = 10,     ///< Default speed of player
    PLAYER_DEFAULT_HEALTH = 3,      ///< Default health of player
    ENEMY_DEFAULT_HEALTH  = 1,      ///< Default health for enemy
    ENEMY_SPAWN_TIMEOUT   = 2000,   ///< An enemy is created every x ms
    BONUS_SPAWN_TIMEOUT   = 30000,  ///< A bonus is created every x ms
    GAME_DIFF_TIMEOUT     = 100000, ///< Game difficulty increases every x ms
    ENEMY_TYPES           = 4,      ///< Number of enemy types
  };
  /**
   * @brief player The player
   */
  Player * player;
  /**
   * @brief effect This is used for playing sound effects for shooting, etc.
   */
  QSoundEffect * effect;
  /**
   * @brief spriteList List of sprites present on the map
   */
  QList<Sprite*> * spriteList;
  /**
   * @brief gamePaused Is game paused
   */
  bool gamePaused;
  /**
   * @brief mouseMoveEnabled Is mouse movement of player enabled
   */
  bool mouseMoveEnabled;
  /**
   * @brief audioEnabled Is audio enabled
   */
  bool audioEnabled;
  /**
   * @brief gameDifficulty Level of difficulty of the game
   * @details It increases as the game progresses.
   */
  int gameDifficulty;
  /**
   * @brief enemyTimer Timer for spawning enemies
   */
  QTimer * enemyTimer;
  /**
   * @brief bonusTimer Timer for creating bonuses
   */
  QTimer * bonusTimer;

};

#endif // GAMESCENE_H
