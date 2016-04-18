#ifndef BACKGROUNDLABEL_H
#define BACKGROUNDLABEL_H

#include <QLabel>
#include <QResizeEvent>

class BackgroundLabel: public QLabel {
public:
  BackgroundLabel(QWidget * parent = 0): QLabel(parent) {
    setPixmap(
          QPixmap(":/images/graphics/background/science-fiction-441708_960_720.jpg").
          scaled(640, 480));
    setScaledContents(true);
//    setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);
  }

  void resizeEvent(QResizeEvent *event) {
    QLabel::resizeEvent(event);
  }

  void paintEvent(QPaintEvent *event) {
//    setPixmap(
//          QPixmap(":/images/graphics/background/science-fiction-441708_960_720.jpg").
//          scaled(size()));
    QLabel::paintEvent(event);
  }


};

#endif // BACKGROUNDLABEL_H
