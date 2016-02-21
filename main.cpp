#include <QApplication>
#include <QGraphicsScene>
#include <QGraphicsView>
#include <QDebug>
#include <QTimer>
#include "enemy.h"
#include "myrect.h"

/**
 * @brief main
 * @param argc
 * @param argv
 * @return
 */
int main(int argc, char *argv[])
{
  QApplication a(argc, argv);

  // create a scene
  QGraphicsScene * scene = new QGraphicsScene();

  // create an item
  MyRect * player = new MyRect();

  player->setRect(0, 0, 100, 100);

  // make rect focusable
  player->setFlag(QGraphicsItem::ItemIsFocusable);
  player->setFocus();

  // add the item to the scene
  scene->addItem(player);

  // scene is invisible - create a view
  QGraphicsView * view = new QGraphicsView(scene);

  view->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
  view->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);

  view->setScene(scene);

  view->setWindowTitle("Game of Rectangles");

  view->setFixedSize(800, 600);

  scene->setSceneRect(0, 0, 800, 600);

  player->setPos(view->width()/2, view->height() - player->rect().height());

  // spawn enemies
  QTimer * timer = new QTimer();
  QObject::connect(timer, SIGNAL(timeout()), player, SLOT(spawn()));

  timer->start(2000);

  // show the view - it is invisible
  view->show();

  return a.exec();
}
