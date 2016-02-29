#include "game.h"
#include <QGraphicsScene>
#include <QDebug>
#include <QTimer>
#include "enemy.h"
#include "player.h"
#include "score.h"
#include <QMediaPlayer>
#include <QBrush>
#include <QImage>
#include <QSoundEffect>
#include <bullet.h>

/**
 * @brief Game::Game
 * @param parent
 */
Game::Game(QWidget * parent) {
  // create a scene
  scene = new QGraphicsScene();
  scene->setSceneRect(0, 0, 800, 600);

  // set background
  setBackgroundBrush(QBrush(QImage(
    ":/images/graphics/background/all-703522_1920.jpg")));

  // scene is invisible - add to view
  setScene(scene);
  setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
  setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
  setWindowTitle("Game of Rectangles");

  setFixedSize(800, 600);

  // create a player with an initial health of 3
  player = new Player(3);

//  player->setRect(0, 0, 100, 100);
  player->setPos(width()/2, height() - 100);

  // make player focusable
  player->setFlag(QGraphicsItem::ItemIsFocusable);
  player->setFocus();

  // add the player to the scene
  scene->addItem(player);

  // create score
  score = new Score();
  scene->addItem(score);

  // spawn enemies
  QTimer * timer = new QTimer();
  QObject::connect(timer, SIGNAL(timeout()), this, SLOT(spawnEnemy()));

  timer->start(2000);

  // play background music
//  QMediaPlayer * music = new QMediaPlayer();
//  music->setMedia(QUrl("qrc:/sounds/dark-ambient-background.mp3"));
  //  music->play();

  // create bullet sound effect
  effect = new QSoundEffect();
  effect->setSource(QUrl("qrc:/sounds/sounds/explosion.wav"));

  connect(player, SIGNAL(shoot(int,int)), this, SLOT(createBullet(int,int)));

}

/**
 * @brief Game::resizeEvent Event handler for resizing event
 * @param event
 */
void Game::resizeEvent(QResizeEvent *event) {
//  QRectF rect = scene->itemsBoundingRect();
//  QSize size = QSize(rect.width(), rect.height());
//  rect.setSize(size);
//  fitInView(rect, Qt::IgnoreAspectRatio);
//  player->resize(size);
}

void Game::enemyKilled(QGraphicsItem * casualty) {
  // increase the score
  score->increase();

  Enemy * enemy = dynamic_cast<Enemy*>(casualty);
  enemy->die();
}

/**
 * @brief Game::createBullet Slot for creating a bullet
 * @param x Initial X position of the bullet
 * @param y Initial Y position of the bullet
 */
void Game::createBullet(int x, int y) {

  // create bullet object
  Bullet * bullet = new Bullet(x,y);
  // add it to the scene
  scene->addItem(bullet);

  // if bullet hits a target call enemyKilled slot of the game
  connect(bullet, SIGNAL(bulletHitTarget(QGraphicsItem*)), this, SLOT(enemyKilled(QGraphicsItem*)));

  // play bullet sound
  effect->setVolume(0.5f);
  effect->play();

}

void Game::spawnEnemy() {
  // create an enemy
  Enemy * enemy = new Enemy(1);
  scene->addItem(enemy);

}
