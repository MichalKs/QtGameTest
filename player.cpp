#include "player.h"
#include <QDebug>
#include <QKeyEvent>
#include <QGraphicsScene>
#include "bullet.h"
#include "enemy.h"
#include <QSound>
#include <QSoundEffect>
#include <QGraphicsView>

/**
 * @brief Player::Player
 * @param parent
 */
Player::Player(int initialHealth, QGraphicsItem * parent):
  QGraphicsPixmapItem(parent) {

  health = initialHealth;

  // set graphics for player
  setPixmap(
        QPixmap(":/images/graphics/fighter/smallfighter0006.png").
        scaled(QSize(width, height), Qt::KeepAspectRatio));

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
  qDebug() << "View width: " << view->width()
           << " height: " << view->height();


  if (event->key() == Qt::Key_Left) {

    if (pos().x() > 0) {
      setPos(x()-speed, y());
    }
  } else if (event->key() == Qt::Key_Right) {

    if (pos().x() + width < view->width()) {
      setPos(x()+speed, y());
    }
  } else if (event->key() == Qt::Key_Space) {
    // shoot bullet
    emit shoot(x()+10, y()-50);
  }
}
