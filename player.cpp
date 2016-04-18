#include "player.h"
#include <QDebug>
#include <QKeyEvent>
#include "bullet.h"
#include "enemy.h"
#include <QSound>
#include <QSoundEffect>
#include <QGraphicsView>
#include <QTimer>
#include <sprite.h>

Player::Player(int initialHealth, int speed, int w, int h, QGraphicsItem * parent):
  Sprite(initialHealth, speed, w, h, parent) {

  // initially player is standing still
  moveDirection = PLAYER_STANDING;

  missileCount = INITIAL_MISSILE_COUNT;

  // set base graphics for player
  setPixmap(QPixmap(":/images/graphics/fighter/smallfighter0006.png").
        scaled(QSize(getMaxWidth(), getMaxHeight()), Qt::KeepAspectRatio));

  // create a timer for player movement animation
  QTimer * animationTimer = new QTimer(this);

  // timeout of the timer causes execution of the animation function
  connect(animationTimer, SIGNAL(timeout()), this, SLOT(movementAnimation()));

  // animation changes every 100 ms
  animationTimer->start(ANIMATION_PERIOD);
}

void Player::keyPressEvent(QKeyEvent *event) {

  // If a key is pressed QGraphicsView alerts QGraphicsScene,
  // which then alerts the item that has focus on the scene.
  // That item runs its keyPressEvent function

  QRectF mRect = sceneBoundingRect();

  if (event->key() == Qt::Key_Left) {

    if (pos().x() > 0) {
      setPos(x()-getSpeed(), y());
    }

    if (moveDirection == PLAYER_STANDING || moveDirection == PLAYER_MOVING_RIGHT) {
      // start playing moving left animation
      moveDirection = PLAYER_MOVING_LEFT;
    }

  } else if (event->key() == Qt::Key_Right) {

    if (x() + boundingRect().width() < scene()->width()) {
      setPos(x() + getSpeed(), y());
    }

    if (moveDirection == PLAYER_STANDING || moveDirection == PLAYER_MOVING_LEFT) {
      // start playing moving right animation
      moveDirection = PLAYER_MOVING_RIGHT;
    }

  } else if (event->key() == Qt::Key_Space) {

    if (missileCount > 0) {
      // shoot bullet
      decreaseMissileCount();
      emit shoot(x()+mRect.width()/8, y()-mRect.height()/2);
    } else {
      emit emptyGun();
    }
  }
}

void Player::mousePressEvent(QGraphicsSceneMouseEvent *) {

  if (missileCount > 0) {
    QRectF mRect = sceneBoundingRect();
    decreaseMissileCount();
    emit shoot(x()+mRect.width()/8, y()-mRect.height()/2);
  } else {
    emit emptyGun();
  }

}

void Player::movementAnimation() {

  static MoveDirection previousMoveDirection = PLAYER_STANDING;
  static int animationCounter;

  if ((moveDirection == PLAYER_STANDING) && (previousMoveDirection == PLAYER_STANDING)) {

    setPixmap(QPixmap(":/images/graphics/fighter/smallfighter0006.png").
      scaled(QSize(getMaxWidth(), getMaxHeight()), Qt::KeepAspectRatio));
    // do nothing
    return;
  } else if ((moveDirection == PLAYER_MOVING_LEFT) &&
             (previousMoveDirection == PLAYER_STANDING ||
              previousMoveDirection == PLAYER_MOVING_RIGHT)) {
    // from standing position, so zero out the animation
    animationCounter = 0;
    animationCounter++;
    moveLeftAnimation(animationCounter);
  } else if ((moveDirection == PLAYER_MOVING_LEFT) &&
             (previousMoveDirection == PLAYER_MOVING_LEFT)) {
    animationCounter++;

    if (animationCounter > 5) {
      animationCounter = 5;
    }
    moveLeftAnimation(animationCounter);

  } else if ((moveDirection == PLAYER_STANDING) &&
             (previousMoveDirection == PLAYER_MOVING_LEFT)) {
    animationCounter--;
    moveLeftAnimation(animationCounter);
  } else if ((moveDirection == PLAYER_MOVING_RIGHT) &&
             (previousMoveDirection == PLAYER_STANDING ||
              previousMoveDirection == PLAYER_MOVING_LEFT)) {
    // from standing position, so zero out the animation
    animationCounter = 0;
    animationCounter++;
    moveRightAnimation(animationCounter);
  } else if ((moveDirection == PLAYER_MOVING_RIGHT) &&
             (previousMoveDirection == PLAYER_MOVING_RIGHT)) {
    animationCounter++;

    if (animationCounter > 5) {
      animationCounter = 5;
    }
    moveRightAnimation(animationCounter);

  } else if ((moveDirection == PLAYER_STANDING) &&
             (previousMoveDirection == PLAYER_MOVING_RIGHT)) {
    animationCounter--;
    moveRightAnimation(animationCounter);
  }

  previousMoveDirection = moveDirection;

}

void Player::moveRightAnimation(const int animationCounter) {

  QString filename = QString(":/images/graphics/fighter/smallfighter%1.png").
      arg(animationCounter+6, 4, 10, QChar('0'));

  setPixmap(QPixmap(filename).
    scaled(QSize(getMaxWidth(), getMaxHeight()), Qt::KeepAspectRatio));
}

void Player::moveLeftAnimation(const int animationCounter) {

  const int base = 10; // decimal base for QString
  const QChar paddingChar = '0';
  const int padNumber = 4;

  QString filename = QString(":/images/graphics/fighter/smallfighter%1.png").
      arg(6-animationCounter, padNumber, base, paddingChar);

  setPixmap(QPixmap(filename).
    scaled(QSize(getMaxWidth(), getMaxHeight()), Qt::KeepAspectRatio));

}
