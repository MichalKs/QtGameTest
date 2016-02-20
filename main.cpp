#include <QApplication>
#include <QGraphicsScene>
#include <QGraphicsView>
#include <QDebug>
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
  MyRect * rect = new MyRect();

  rect->setRect(0, 0, 100, 100);

  // make rect focusable
  rect->setFlag(QGraphicsItem::ItemIsFocusable);
  rect->setFocus();

  // add the item to the scene
  scene->addItem(rect);

  // scene is invisible - create a view
  QGraphicsView * view = new QGraphicsView(scene);
  view->setScene(scene);

  // show the view - it is invisible
  view->show();

  return a.exec();
}
