#include "gamescene.h"
#include "bullet.h"
#include "player.h"
#include "enemy.h"
#include <QDebug>
#include <QEvent>
#include <QPushButton>
#include <QTimer>
#include <QGraphicsProxyWidget>
#include <QSoundEffect>
#include <QObject>

GameScene::GameScene(QObject * parent): QGraphicsScene(parent) {

  spriteList = new QList<Sprite*>;
  gamePaused = false;
  mouseMoveEnabled = true;
  audioEnabled = true;

  setSceneRect(0, 0, 800, 600);

  // set background
  setBackgroundBrush(QBrush(QImage(
    ":/images/graphics/background/all-703522_1920.jpg")));

  // create a player with an initial health of 3
  player = new Player(3, 10);
  player->setPos(width()/2, height() - 100);

  // make player focusable
  player->setFlag(QGraphicsItem::ItemIsFocusable);
  player->setFocus();

  // add the player to the scene
  addItem(player);

  // playing with items
  addEllipse(200, 200, 100, 200,
                    QPen(Qt::green, 13, Qt::DashDotLine, Qt::RoundCap, Qt::RoundJoin),
                    QBrush(Qt::red, Qt::FDiagPattern));

  addLine(400, 200, 500, 580,
                 QPen(Qt::cyan, 13, Qt::DashLine, Qt::RoundCap, Qt::RoundJoin));

  QPolygonF poly;

  poly << QPointF(700, 50) << QPointF(600, 150) << QPointF(800, 150);

  addPolygon(poly, QPen(Qt::green, 13, Qt::DashDotLine, Qt::RoundCap, Qt::RoundJoin),
                    QBrush(Qt::red, Qt::FDiagPattern));

  addSimpleText(QString("Hello world!!!"), QFont("Fantasy", 72, QFont::Bold));

  QPushButton * b = new QPushButton(QString("Spawn enemy"));

  QGraphicsProxyWidget * p = addWidget(b);
  p->setPos(500, 500);

  connect(b, SIGNAL(clicked(bool)), this, SLOT(pauseGame(bool)));

  // spawn enemies
  QTimer * timer = new QTimer();
  QObject::connect(timer, SIGNAL(timeout()), this, SLOT(spawnEnemy()));

  timer->start(2000);


  // create bullet sound effect
  effect = new QSoundEffect();
  effect->setSource(QUrl("qrc:/sounds/sounds/explosion.wav"));

  connect(player, SIGNAL(shoot(int,int)), this, SLOT(createBullet(int,int)));
  connect(player, SIGNAL(healthChanged(int)), this, SLOT(playerHealthDecreased(int)));
  connect(player, SIGNAL(theKingIsDead()), this, SLOT(playerDied()));

  qDebug() << focusItem();

}

/**
 * @brief Game::createBullet Slot for creating a bullet
 * @param x Initial X position of the bullet
 * @param y Initial Y position of the bullet
 */
void GameScene::createBullet(int x, int y) {

  // create bullet object
  Bullet * bullet = new Bullet(x,y);
  // add it to the scene
  addItem(bullet);

  // if bullet hits a target call enemyKilled slot of the game
  connect(bullet, SIGNAL(bulletHitTarget(QGraphicsItem*)), this, SLOT(enemyKilled(QGraphicsItem*)));

  if (audioEnabled) {
    // play bullet sound
    effect->setVolume(0.5f);
    effect->play();
  }


}

void GameScene::enemyKilled(QGraphicsItem * casualty) {
  // increase the score
  emit increaseScore(1);

  Enemy * enemy = dynamic_cast<Enemy*>(casualty);
  enemy->die();
}

void GameScene::spawnEnemy() {
  if (!gamePaused) {
    // create an enemy
    Enemy * enemy = new Enemy(1);
    addItem(enemy);
    connect(enemy, SIGNAL(enemyHitTarget()), player, SLOT(gotHit()));
  }
}

void GameScene::pauseGame(bool isPaused) {

  gamePaused = isPaused;

  qDebug() << "Pause game slot";
  if (isPaused == true) {
    for (int i = 0; i < spriteList->size(); i++ ) {
      spriteList->at(i)->pause();
    }
  } else {
    for (int i = 0; i < spriteList->size(); i++ ) {
      spriteList->at(i)->unpause();
    }
  }

}

void GameScene::playerHealthDecreased(int h) {
  emit playerHealthChanged(h);
}

bool GameScene::event(QEvent *event) {

//  event->type();
  QGraphicsScene::event(event);

}

void GameScene::keyPressEvent(QKeyEvent * event) {
  if (!gamePaused) {
    player->setFocus();
    QGraphicsScene::keyPressEvent(event);
  }
}



void GameScene::mousePressEvent(QGraphicsSceneMouseEvent * mouseEvent) {
//  qDebug() << "Mouse presss event received in scene";
  if (!gamePaused && mouseMoveEnabled) {
    player->mousePressEvent(mouseEvent);
  }

}

void GameScene::mouseMoveEvent(QGraphicsSceneMouseEvent *mouseEvent) {
//  qDebug() << "Mouse move event received in scene";
  if (!gamePaused && mouseMoveEnabled) {
    player->mouseMoveEvent(mouseEvent);
  }
}

void GameScene::addItem(QGraphicsItem *item) {
  qDebug() << "Scene item added";

  Sprite * spr = dynamic_cast<Sprite*>(item);

  if (spr) {

    spriteList->append(spr);
    qDebug() << "Sprite added";
  }

  QGraphicsScene::addItem(item);
}

void GameScene::removeItem(QGraphicsItem *item) {
  qDebug() << "Scene item removed";

  Sprite * spr = dynamic_cast<Sprite*>(item);

  if (spr) {

    spriteList->removeAt(spriteList->indexOf(spr));
    qDebug() << "Sprite removed";
  }

  QGraphicsScene::removeItem(item);
}
