#include "player.h"
#include <QDebug>
#include <QKeyEvent>
#include <QGraphicsScene>
#include "bullet.h"
#include "enemy.h"
#include <QSound>
#include <QSoundEffect>

Player::Player(QGraphicsItem * parent) : QGraphicsPixmapItem(parent)
{
  bulletSound = new QMediaPlayer();
  bulletSound->setMedia(QUrl("qrc:/sounds/sounds/explosion.wav"));

  effect = new QSoundEffect();
  effect->setSource(QUrl("qrc:/sounds/sounds/explosion.wav"));

  // set graphics
  setPixmap(
        QPixmap(":/images/graphics/fighter/smallfighter0006.png").
        scaled(QSize(100, 100),Qt::KeepAspectRatio));

}

void Player::keyPressEvent(QKeyEvent *event)
{

  // if a key is pressed QGraphicsView alerts QGraphicsScene, which then
  // alerts the item that has focus on the scene. That item runs its keyPressEvent
  // function

  if (event->key() == Qt::Key_Left)
  {
    if (pos().x() > 0)
    {
      setPos(x()-10, y());
    }
  }
  else if (event->key() == Qt::Key_Right)
  {
    if (pos().x() + 100 < 800)
    {
      setPos(x()+10, y());
    }
  }
  else if (event->key() == Qt::Key_Space)
  {
    // shoot bullet
    Bullet * bullet = new Bullet();
    bullet->setPos(x()+50, y());
    scene()->addItem(bullet);

    // play bullet sound
    //QSound::play(":/sounds/explosion.wav");
//    effect.setLoopCount(QSoundEffect::Infinite);
    effect->setVolume(0.5f);
    effect->play();

    // play bulletsound
//    if (bulletSound->state() == QMediaPlayer::PlayingState){
//        bulletSound->setPosition(0);
//    }
//    else if (bulletSound->state() == QMediaPlayer::StoppedState){
//        bulletSound->play();
//    }

  }

}

void Player::spawn()
{
  // create an enemy
  Enemy * enemy = new Enemy();
  scene()->addItem(enemy);

}
