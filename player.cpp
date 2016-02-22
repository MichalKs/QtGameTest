#include "player.h"
#include <QDebug>
#include <QKeyEvent>
#include <QGraphicsScene>
#include "bullet.h"
#include "enemy.h"
#include <QSound>
#include <QSoundEffect>

Player::Player()
{
  bulletSound = new QMediaPlayer();
  bulletSound->setMedia(QUrl("qrc:/sounds/explosion.wav"));

  effect = new QSoundEffect();
  effect->setSource(QUrl("qrc:/sounds/explosion.wav"));

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
    if (pos().x() + rect().width() < 800)
    {
      setPos(x()+10, y());
    }
  }
  else if (event->key() == Qt::Key_Space)
  {
    // shoot bullet
    Bullet * bullet = new Bullet();
    bullet->setPos(x()+rect().width()/2-bullet->rect().width()/2, y());
    scene()->addItem(bullet);

    // play bullet sound
    //QSound::play(":/sounds/explosion.wav");
//    effect.setLoopCount(QSoundEffect::Infinite);
//    effect.setVolume(0.25f);
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
