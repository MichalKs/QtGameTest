#include "game.h"
#include <QDebug>
#include <QTimer>
#include "enemy.h"
#include "player.h"
#include <QMediaPlayer>
#include <QBrush>
#include <QImage>
#include <QSoundEffect>
#include <bullet.h>
#include <QMouseEvent>
#include <gamescene.h>
#include <QPolygonF>
#include <QPointF>
#include <QPushButton>
#include <QGraphicsProxyWidget>

/**
 * @brief Game::Game
 * @param parent
 */
Game::Game(QWidget * parent) {

  // create a player with an initial health of 3
  player = new Player(3, 10);

  // create a scene
  scene = new GameScene(player);
  scene->setSceneRect(0, 0, 800, 600);

  // set background
  scene->setBackgroundBrush(QBrush(QImage(
    ":/images/graphics/background/all-703522_1920.jpg")));

  // scene is invisible - add to view
  setScene(scene);
  setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
  setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
  setWindowTitle("Game of Rectangles");

  setFixedSize(800, 600);

  // hide cursor
  setCursor(Qt::CrossCursor);

//  QPoint glob = mapToGlobal(QPoint(width()/2,height()/2));
//  QCursor::setPos(glob);

//  player->setRect(0, 0, 100, 100);
  player->setPos(width()/2, height() - 100);

  // make player focusable
  player->setFlag(QGraphicsItem::ItemIsFocusable);
  player->setFocus();

  // add the player to the scene
  scene->addItem(player);

  // playing with items
  scene->addEllipse(200, 200, 100, 200,
                    QPen(Qt::green, 13, Qt::DashDotLine, Qt::RoundCap, Qt::RoundJoin),
                    QBrush(Qt::red, Qt::FDiagPattern));

  scene->addLine(400, 200, 500, 580,
                 QPen(Qt::cyan, 13, Qt::DashLine, Qt::RoundCap, Qt::RoundJoin));

  QPolygonF poly;

  poly << QPointF(700, 50) << QPointF(600, 150) << QPointF(800, 150);

  scene->addPolygon(poly, QPen(Qt::green, 13, Qt::DashDotLine, Qt::RoundCap, Qt::RoundJoin),
                    QBrush(Qt::red, Qt::FDiagPattern));

  scene->addSimpleText(QString("Hello world!!!"), QFont("Fantasy", 72, QFont::Bold));

  QPushButton * b = new QPushButton(QString("Spawn enemy"));

  QGraphicsProxyWidget * p = scene->addWidget(b);
  p->setPos(500, 500);

  connect(b, SIGNAL(clicked(bool)), this, SLOT(spawnEnemy()));

  //scene->clearFocus();

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

  qDebug() << scene->focusItem();
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

void Game::keyPressEvent(QKeyEvent *event) {
  player->setFocus();
  QGraphicsView::keyPressEvent(event);
}

void Game::mousePressEvent(QMouseEvent * event) {
//  qDebug() << "Mouse event";
  QGraphicsView::mousePressEvent(event);
}

void Game::enemyKilled(QGraphicsItem * casualty) {
  // increase the score
  emit increaseScore(1);

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
