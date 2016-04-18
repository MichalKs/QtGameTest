#include <QDebug>
#include "game.h"
#include "gamescene.h"
#include <QResizeEvent>

Game::Game(QWidget * parent): QGraphicsView(parent) {

  // create a scene, make it a child of the view
  scene = new GameScene(this);
  // scene is invisible - add it to view
  setScene(scene);
//  scene->setSceneRect(0, 0, size().width(), size().height());
  // disable scroll bars
  setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
  setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);

//  // set fixed size
//  setSize(800, 600);

  // make the cursor a cross for aiming
  setCursor(Qt::CrossCursor);

  // track move events in view
  setMouseTracking(true);

}

void Game::resizeEvent(QResizeEvent *event) {
//  QRectF rect = scene->itemsBoundingRect();
//  QSize size = QSize(rect.width(), rect.height());
//  rect.setSize(size);
//  fitInView(rect, Qt::IgnoreAspectRatio);
  //  player->resize(size);

//  scene->setSceneRect(0, 0, event->size().width(), event->size().height());
//
//  fitInView(sceneRect());
  fitInView(0, 0, 800, 600);

  QGraphicsView::resizeEvent(event);
}

void Game::keyPressEvent(QKeyEvent *event) {
//  qDebug() << "Key press event received in view";
  QGraphicsView::keyPressEvent(event);
}

void Game::mousePressEvent(QMouseEvent * event) {
//  qDebug() << "Mouse press event received in view";
  QGraphicsView::mousePressEvent(event);
}
void Game::mouseMoveEvent(QMouseEvent *event) {
//  qDebug() << "Mouse move event received in view";
  QGraphicsView::mouseMoveEvent(event);
}
