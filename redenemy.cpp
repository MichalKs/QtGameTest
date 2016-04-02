#include "redenemy.h"
#include "gamescene.h"

void RedEnemy::dieAnimation() {

  const int numberOfAnimationFrames = 10;
  static int animationCounter;

  QString filename = QString(":/images/graphics/explosion/yellowexplosion/Explosion_%1.png").
      arg(animationCounter+1, 3, 10, QChar('0'));

//  qDebug() << filename;

  // if animation is done then remove object from scene and memory
  if (animationCounter == numberOfAnimationFrames) {
    animationCounter = 0;
    GameScene * s = dynamic_cast<GameScene*> (QGraphicsItem::scene());
    s->removeItem(this);
    delete this;
  } else {
    setPos(x()-getMaxWidth()/20, y()-getMaxHeight()/20);
    setPixmap(QPixmap(filename).
              scaled(QSize(getMaxWidth()*1.5, getMaxHeight()*1.5),Qt::KeepAspectRatio));
  }

  animationCounter++;

}
