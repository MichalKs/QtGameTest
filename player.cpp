#include "player.h"
#include <QDebug>
#include <QKeyEvent>
#include <QGraphicsScene>
#include "bullet.h"
#include "enemy.h"
#include <QSound>
#include <QSoundEffect>
#include <QGraphicsView>
#include <QTimer>
#include <sprite.h>
#include <QGraphicsSceneMouseEvent>

/**
 * @brief Player::Player
 * @param parent
 */
Player::Player(int initialHealth, int speed, int w, int h, QGraphicsItem * parent):
  Sprite(initialHealth, speed, w, h, parent) {

  // initially player is standing still
  moveDirection = PLAYER_STANDING;

  // set base graphics for player
  setPixmap(QPixmap(":/images/graphics/fighter/smallfighter0006.png").
        scaled(QSize(getMaxWidth(), getMaxHeight()), Qt::KeepAspectRatio));

  // create a timer for player movement animation
  animationTimer = new QTimer();

  // timeout of the timer causes execution of the animation function
  connect(animationTimer, SIGNAL(timeout()), this, SLOT(movementAnimation()));

  // animation changes every 100 ms
  animationTimer->start(animationPeriod);
}

Player::~Player() {
  // delete all heap resources
  delete animationTimer;
}

void Player::resize(QSize &size) {
  // set base graphics for player
//  setPixmap(QPixmap(":/images/graphics/fighter/smallfighter0006.png").
//        scaled(QSize(width, height), Qt::KeepAspectRatio));
}

/**
 * @brief Player::keyPressEvent
 * @param event
 */
void Player::keyPressEvent(QKeyEvent *event) {

  // If a key is pressed QGraphicsView alerts QGraphicsScene,
  // which then alerts the item that has focus on the scene.
  // That item runs its keyPressEvent function

  // Get size of view to know bounds
  QList<QGraphicsView *> viewList = scene()->views();
  QGraphicsView *view = viewList.first();
//  qDebug() << "View width: " << view->width()
//           << " height: " << view->height();

  QRectF mRect = sceneBoundingRect();
//  qDebug() << "Item width: " << mRect.width()
//           << " height: " << mRect.height();

  if (event->key() == Qt::Key_Left) {

    if (pos().x() > 0) {
      setPos(x()-getSpeed(), y());
    }

    if (moveDirection == PLAYER_STANDING || moveDirection == PLAYER_MOVING_RIGHT) {
      // start playing moving left animation
      moveDirection = PLAYER_MOVING_LEFT;
    }

  } else if (event->key() == Qt::Key_Right) {

    if (x() + getMaxWidth() < view->width()) {
      setPos(x() + getSpeed(), y());
    }

    if (moveDirection == PLAYER_STANDING || moveDirection == PLAYER_MOVING_LEFT) {
      // start playing moving right animation
      moveDirection = PLAYER_MOVING_RIGHT;
    }

  } else if (event->key() == Qt::Key_Space) {
    // shoot bullet
    emit shoot(x()+mRect.width()/8, y()-mRect.height()/2);
  }
}

void Player::mousePressEvent(QGraphicsSceneMouseEvent * event) {

  QRectF mRect = sceneBoundingRect();
//  qDebug() << "Mouse event in player";
  emit shoot(x()+mRect.width()/8, y()-mRect.height()/2);

}

void Player::mouseMoveEvent(QGraphicsSceneMouseEvent *event) {
//  qDebug() << "Mouse move event in player";
  if (event->scenePos().x() < 750) {
    setPos(event->scenePos().x(), y());
  }

}

void Player::keyReleaseEvent(QKeyEvent *event) {
  // if key is realeased the player should stand still
  moveDirection = PLAYER_STANDING;
}

void Player::gotHit() {
  decreaseHealth();
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

  // animationTimer->stop();
}

void Player::moveRightAnimation(const int animationCounter) {

  QString filename = QString(":/images/graphics/fighter/smallfighter%1.png").
      arg(animationCounter+6, 4, 10, QChar('0'));

//  qDebug() << filename;

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
