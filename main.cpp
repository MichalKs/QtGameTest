#include <QApplication>
#include <QGraphicsScene>
#include <QGraphicsView>
#include <QGraphicsRectItem>

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

  // create an item to put on the scene
  QGraphicsRectItem * rect = new QGraphicsRectItem();

  rect->setRect(0, 0, 100, 100);

  // add the item to the scene
  scene->addItem(rect);

  // scene is invisible - create a view
  QGraphicsView * view = new QGraphicsView(scene);
  view->setScene(scene);

  view->show();

  return a.exec();
}
