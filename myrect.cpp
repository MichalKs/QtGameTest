#include "myrect.h"
#include <QDebug>
#include <QKeyEvent>

MyRect::MyRect()
{

}

void MyRect::keyPressEvent(QKeyEvent *event)
{

  // if a key is pressed QGraphicsView alerts QGraphicsScene, which then
  // alerts the item that has focus on the scene. That item runs its keyPressEvent
  // function


  qDebug() << "You pressed a key";

  if (event->key() == Qt::Key_Left)
  {
    setPos(x()-10, y());
  }
  else if (event->key() == Qt::Key_Right)
  {
    setPos(x()+10, y());
  }
  else if (event->key() == Qt::Key_Up)
  {
    setPos(x(), y()-10);
  }
  else if (event->key() == Qt::Key_Down)
  {
    setPos(x(), y()+10);
  }

}
