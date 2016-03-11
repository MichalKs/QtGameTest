#ifndef STATUSBAR_H
#define STATUSBAR_H

#include <QWidget>

class QLabel;
class QHBoxLayout;
class QVBoxLayout;

class Statusbar: public QWidget {
  Q_OBJECT
public:
  Statusbar(QWidget * parent = 0);

public slots:
  void increaseScore(int increment);

private:
  QLabel * scoreLabel;
  QLabel * healthLabel;
  QLabel * scoreIconLabel;
  QLabel * healthIconLabel;
  QLabel * weaponLabel;
  QLabel * weaponIconLabel;
  QHBoxLayout * hLayout1;
  QVBoxLayout * healthLayout;
  QVBoxLayout * scoreLayout;
  QVBoxLayout * weaponLayout;

  int score;
};

#endif // STATUSBAR_H
