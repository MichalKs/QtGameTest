#include "game.h"
#include <QGraphicsScene>
#include <QDebug>
#include <QTimer>
#include "enemy.h"
#include "player.h"
#include "score.h"
#include "health.h"
#include <QMediaPlayer>
#include <QBrush>
#include <QImage>

Game::Game(QWidget * parent)
{
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

  // create a player
  player = new Player();

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

  // create health
  health = new Health();
  health->setPos(health->x(), health->y()+25);
  scene->addItem(health);


  // spawn enemies
  QTimer * timer = new QTimer();
  QObject::connect(timer, SIGNAL(timeout()), player, SLOT(spawn()));

  timer->start(2000);

  // play background music
//  QMediaPlayer * music = new QMediaPlayer();
//  music->setMedia(QUrl("qrc:/sounds/dark-ambient-background.mp3"));
//  music->play();
}
