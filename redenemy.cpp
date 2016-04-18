#include "redenemy.h"
#include "gamescene.h"

void RedEnemy::dieAnimation() {

  const int numberOfAnimationFrames = 10;
  const double explosionScaleFactor = 1.5;
  static int animationCounter;

  // construct the PNG name based on animationCounter - see file names
  QString filename = QString(":/images/graphics/explosion/yellowexplosion/Explosion_%1.png").
      arg(animationCounter+1, 3, 10, QChar('0'));

  // if animation is done then remove object from scene and memory
  if (animationCounter == numberOfAnimationFrames) {
    animationCounter = 0;
    GameScene * s = dynamic_cast<GameScene*> (QGraphicsItem::scene());
    s->removeItem(this);
    delete this;
  } else {
    // if animation is not done display next frame
    // the explosion is moving
    setPos(x()-getMaxWidth()/20, y()-getMaxHeight()/20);
    setPixmap(QPixmap(filename).
              scaled(QSize(getMaxWidth()*explosionScaleFactor,
                           getMaxHeight()*explosionScaleFactor),
                     Qt::KeepAspectRatio));
  }

  animationCounter++;

}
