#include "gamescene.h"
#include "bullet.h"
#include "bonus.h"
#include "player.h"
#include "yellowenemy.h"
#include "redenemy.h"
#include "darkinvader.h"
#include "alienspaceship.h"
#include <QDebug>
#include <QEvent>
#include <QTimer>
#include <QSoundEffect>

GameScene::GameScene(QObject * parent): QGraphicsScene(parent) {

//  spriteList        = new QList<Sprite*>;
  gamePaused        = false;
  mouseMoveEnabled  = true;
  audioEnabled      = true;

  // set scene dimensions
  setSceneRect(0, 0, SCENE_WIDTH, SCENE_HEIGHT);

  // set background of the scene
  setBackgroundBrush(QBrush(QImage(
    ":/images/graphics/background/all-703522_1920.jpg")));

  // create a player with an initial health of 3 and a speed of 10
  player = new Player(PLAYER_DEFAULT_HEALTH, PLAYER_DEFAULT_SPEED);
  // add the player to the scene
  addItem(player);
  // place it at a reasonable position (middle of bottom)
  player->setPos(width()/2, height() - player->boundingRect().width()*1.6);

  // make player focusable and set focus to it (keyboard focus)
  player->setFlag(QGraphicsItem::ItemIsFocusable);
  player->setFocus();

  // when player shoots create bullet
  connect(player, SIGNAL(shoot(int,int)),     this, SLOT(createBullet(int,int)));
  // when player health is decreased inform statusbar
  connect(player, SIGNAL(healthChanged(int)), this, SLOT(playerHealthDecreased(int)));
  // when player dies inform main window
  connect(player, SIGNAL(theKingIsDead()),    this, SLOT(playerDied()));
  // when player shoots inform statusbar
  connect(player, SIGNAL(missileCountChanged(int)), this, SLOT(playerMissileCountChanged(int)));
  // when we run out of missiles - play an empty gun sound
  connect(player, SIGNAL(emptyGun()), this, SLOT(fireEmptyGun()));

  // create timer to spawn enemies
  enemyTimer = new QTimer(this);
  QObject::connect(enemyTimer, SIGNAL(timeout()), this, SLOT(spawnEnemy()));
  enemyTimer->start(ENEMY_SPAWN_TIMEOUT);

  bonusTimer = new QTimer(this);
  QObject::connect(bonusTimer, SIGNAL(timeout()), this, SLOT(spawnBonuses()));
  bonusTimer->start(BONUS_SPAWN_TIMEOUT);

  QTimer * difficultyRiseTimer = new QTimer(this);
  QObject::connect(difficultyRiseTimer, SIGNAL(timeout()), this, SLOT(increaseDifficulty()));
  difficultyRiseTimer->start(GAME_DIFF_TIMEOUT);

  // create bullet sound effect
  effect = new QSoundEffect(this);
  effect->setSource(QUrl("qrc:/sounds/sounds/explosion.wav"));

}

void GameScene::createBullet(int x, int y) {

  const float bulletSoundVolume = 0.5f;

  // create bullet object
  Bullet * bullet = new Bullet(x,y);
  // add it to the scene
  addItem(bullet);

  // if bullet hits a target call enemyKilled slot of the game
  connect(bullet, SIGNAL(bulletHitTarget(QGraphicsItem*)), this, SLOT(enemyKilled(QGraphicsItem*)));

  // play bullet sound if audio is enabled
  if (audioEnabled) {
    effect->setSource(QUrl("qrc:/sounds/sounds/explosion.wav"));
    effect->setVolume(bulletSoundVolume);
    effect->play();
  }

}

void GameScene::enemyKilled(QGraphicsItem * casualty) {

  const int scoreDelta = 1; // increase score by 1

  // cast casualty to Enemy object
  Enemy * enemy = dynamic_cast<Enemy*>(casualty);
  // if cast is successful
  if (enemy) {
    // increase the score
    emit increaseScore(scoreDelta);
    enemy->decreaseHealth();
  }

}

void GameScene::spawnEnemy() {

  // if game is unpaused create more enemies
  if (!gamePaused) {

    int enemyType = rand() % ENEMY_TYPES;

    Enemy * enemy;

    switch (enemyType) {

    case 0:
      enemy = new YellowEnemy();
      break;
    case 1:
      enemy = new RedEnemy();
      break;
    case 2:
      enemy = new DarkInvader();
      break;
    case 3:
      enemy = new AlienSpaceship();
      break;
    default:
      enemy = new DarkInvader();
    }

    // add enemy to scene
    addItem(enemy);
    // if enemy crashes into player then he takes damage
    connect(enemy, SIGNAL(enemyHitTarget()), player, SLOT(gotHit()));
  }
}

void GameScene::spawnBonuses() {
  // if game is unpaused create more bonuses
  if (!gamePaused) {

    // set random position
    int possiblePositions = SCENE_WIDTH - 100;
    int randomNumber = rand() % possiblePositions;

    Bonus * bonus = new Bonus(randomNumber, 0);

    // add bonus to scene
    addItem(bonus);
    connect(bonus, SIGNAL(playerGetsBonus()), player, SLOT(getBonus()));
  }
}

void GameScene::pauseGame(bool isPaused) {

  gamePaused = isPaused;

  if (isPaused == true) {
    qDebug() << "Pausing game";
    // pause all sprites
    for (int i = 0; i < spriteList.size(); i++ ) {
      spriteList.at(i)->pause();
    }
  } else {
    qDebug() << "Unpausing game";
    // unpause all sprites
    for (int i = 0; i < spriteList.size(); i++ ) {
      spriteList.at(i)->unpause();
    }
  }

}

void GameScene::increaseDifficulty() {

  const double difficultyDelta = 0.1;
  const double maximumDifficulty = 0.9;

  gameDifficulty += difficultyDelta;
  if (gameDifficulty >= maximumDifficulty) {
    gameDifficulty = maximumDifficulty;
  }
  // Decrease enemy creation period
  enemyTimer->stop();
  enemyTimer->start(ENEMY_SPAWN_TIMEOUT*(1-gameDifficulty));
  // Decrease bonus creation period
  bonusTimer->stop();
  bonusTimer->start(BONUS_SPAWN_TIMEOUT*(1-gameDifficulty));

}

void GameScene::addItem(QGraphicsItem *item) {

  qDebug() << "Adding item to list";
  Sprite * spr = dynamic_cast<Sprite*>(item);

  if (spr) {
    spriteList.append(spr);
  }

  QGraphicsScene::addItem(item);
}

void GameScene::removeItem(QGraphicsItem *item) {

  qDebug() << "Removing item from list";
  Sprite * spr = dynamic_cast<Sprite*>(item);

  if (spr) {
    spriteList.removeAt(spriteList.indexOf(spr));
  }

  QGraphicsScene::removeItem(item);
}
