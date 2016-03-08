#include "gamescene.h"
#include <QDebug>
#include <QEvent>

GameScene::GameScene(Player * player): QGraphicsScene() {
  playerPtr = player;
}

bool GameScene::event(QEvent *event) {

//  event->type();


  QGraphicsScene::event(event);

}

void GameScene::mousePressEvent(QGraphicsSceneMouseEvent * mouseEvent) {
  qDebug() << "Mouse presss event received in scene";
  playerPtr->mousePressEvent(mouseEvent);
}

void GameScene::mouseMoveEvent(QGraphicsSceneMouseEvent *mouseEvent) {
  qDebug() << "Mouse move event received in scene";
  playerPtr->mouseMoveEvent(mouseEvent);

}
