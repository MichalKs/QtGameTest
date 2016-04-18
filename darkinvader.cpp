#include "darkinvader.h"
#include "gamescene.h"

void DarkInvader::dieAnimation() {

  const int numberOfAnimationFrames = 13;
  static int animationCounter;

  // construct the PNG name based on animationCounter - see file names
  QString filename = QString(":/images/graphics/explosion/purpleexplosion/Explosion_%1.png").
      arg(animationCounter+1, 3, 10, QChar('0'));

  // if animation is done then remove object from scene and memory
  if (animationCounter == numberOfAnimationFrames) {
    animationCounter = 0;
    GameScene * s = dynamic_cast<GameScene*> (QGraphicsItem::scene());
    s->removeItem(this);
    delete this;
  } else {
    // if animation is not done display next frame
    setPixmap(QPixmap(filename).
              scaled(QSize(getMaxWidth(), getMaxHeight()), Qt::KeepAspectRatio));
  }

  animationCounter++;

}
