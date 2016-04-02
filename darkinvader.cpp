#include "darkinvader.h"
#include "gamescene.h"

void DarkInvader::dieAnimation() {

  const int numberOfAnimationFrames = 13;
  static int animationCounter;

  QString filename = QString(":/images/graphics/explosion/purpleexplosion/Explosion_%1.png").
      arg(animationCounter+1, 3, 10, QChar('0'));

//  qDebug() << filename;

  // if animation is done then remove object from scene and memory
  if (animationCounter == numberOfAnimationFrames) {
    animationCounter = 0;
    GameScene * s = dynamic_cast<GameScene*> (QGraphicsItem::scene());
    s->removeItem(this);
    delete this;
  } else {
    setPixmap(QPixmap(filename).
              scaled(QSize(getMaxWidth(), getMaxHeight()), Qt::KeepAspectRatio));
  }

  animationCounter++;

}
