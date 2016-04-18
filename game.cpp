#include <QDebug>
#include "game.h"
#include "gamescene.h"
#include <QResizeEvent>

Game::Game(QWidget * parent): QGraphicsView(parent) {

  // create a scene, make it a child of the view
  scene = new GameScene(this);
  // scene is invisible - add it to view
  setScene(scene);

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
