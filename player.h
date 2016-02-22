#ifndef PLAYER_H
#define PLAYER_H

#include <QGraphicsRectItem>
#include <QMediaPlayer>

class QSoundEffect;

class Player: public QObject, public QGraphicsRectItem
{

  Q_OBJECT
public:

  Player();

  void keyPressEvent(QKeyEvent * event);

public slots:
  void spawn();

private:
  QMediaPlayer * bulletSound;
  QSoundEffect * effect;
};

#endif // PLAYER_H
