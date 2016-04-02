#include "gamescene.h"
#include "bullet.h"
#include "player.h"
#include "yellowenemy.h"
#include "redenemy.h"
#include "darkinvader.h"
#include "alienspaceship.h"
#include <QDebug>
#include <QEvent>
//#include <QPushButton>
#include <QTimer>
//#include <QGraphicsProxyWidget>
#include <QSoundEffect>

GameScene::GameScene(QObject * parent): QGraphicsScene(parent) {

  spriteList        = new QList<Sprite*>;
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
  // when player dies inform main widnow
  connect(player, SIGNAL(theKingIsDead()),    this, SLOT(playerDied()));

  // create timer to spawn enemies
  QTimer * timer = new QTimer(this);
  QObject::connect(timer, SIGNAL(timeout()), this, SLOT(spawnEnemy()));
  timer->start(2000);

  // create bullet sound effect
  effect = new QSoundEffect(this);
  effect->setSource(QUrl("qrc:/sounds/sounds/explosion.wav"));

  // playing with items
//  addEllipse(200, 200, 100, 200,
//                    QPen(Qt::green, 13, Qt::DashDotLine, Qt::RoundCap, Qt::RoundJoin),
//                    QBrush(Qt::red, Qt::FDiagPattern));

//  addLine(400, 200, 500, 580,
//                 QPen(Qt::cyan, 13, Qt::DashLine, Qt::RoundCap, Qt::RoundJoin));

//  QPolygonF poly;

//  poly << QPointF(700, 50) << QPointF(600, 150) << QPointF(800, 150);

//  addPolygon(poly, QPen(Qt::green, 13, Qt::DashDotLine, Qt::RoundCap, Qt::RoundJoin),
//                    QBrush(Qt::red, Qt::FDiagPattern));

//  addSimpleText(QString("Hello world!!!"), QFont("Fantasy", 72, QFont::Bold));

//  QPushButton * b = new QPushButton(QString("Spawn enemy"));

//  QGraphicsProxyWidget * p = addWidget(b);
//  p->setPos(500, 500);

//  connect(b, SIGNAL(clicked(bool)), this, SLOT(pauseGame(bool)));

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

    int enemyType = rand() % 4;
    qDebug() << "Creating enemy number " << enemyType;

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

    // create an enemy
    addItem(enemy);
    // if enemy crashes into player then he takes damage
    connect(enemy, SIGNAL(enemyHitTarget()), player, SLOT(gotHit()));
  }
}

void GameScene::pauseGame(bool isPaused) {

  gamePaused = isPaused;

  qDebug() << "Pause game slot";
  if (isPaused == true) {
    // pause all sprites
    for (int i = 0; i < spriteList->size(); i++ ) {
      spriteList->at(i)->pause();
    }
  } else {
    // unpause all sprites
    for (int i = 0; i < spriteList->size(); i++ ) {
      spriteList->at(i)->unpause();
    }
  }

}

void GameScene::keyPressEvent(QKeyEvent * event) {
  if (!gamePaused) {
    // change focus to player to get keyboard events
    player->setFocus();
    // this will pass event to focus item
    QGraphicsScene::keyPressEvent(event);
  }
}

void GameScene::mousePressEvent(QGraphicsSceneMouseEvent * mouseEvent) {
//  qDebug() << "Mouse press event received in scene";
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
//  qDebug() << "Scene item added";

  Sprite * spr = dynamic_cast<Sprite*>(item);

  if (spr) {
    spriteList->append(spr);
  }

  QGraphicsScene::addItem(item);
}

void GameScene::removeItem(QGraphicsItem *item) {
//  qDebug() << "Scene item removed";

  Sprite * spr = dynamic_cast<Sprite*>(item);

  if (spr) {
    spriteList->removeAt(spriteList->indexOf(spr));
  }

  QGraphicsScene::removeItem(item);
}
