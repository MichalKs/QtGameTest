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
 * @brief Game::Game Constructor for Game view object
 * @param parent
 */
Game::Game(QWidget * parent) {

  // create a scene
  scene = new GameScene();

  // scene is invisible - add to view
  setScene(scene);
  setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
  setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
  setWindowTitle("Game of Rectangles");

  setFixedSize(800, 600);

  // hide cursor
  setCursor(Qt::CrossCursor);
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
  QGraphicsView::keyPressEvent(event);
}

void Game::mousePressEvent(QMouseEvent * event) {
  QGraphicsView::mousePressEvent(event);
}
