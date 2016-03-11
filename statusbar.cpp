#include "statusbar.h"
#include <QLabel>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QGraphicsEffect>
#include <QPixmap>
#include <QTransform>

Statusbar::Statusbar(QWidget * parent): QWidget(parent) {

  QPalette pal(palette());

  // set black background
  pal.setColor(QPalette::Background, Qt::black);
  setAutoFillBackground(true);
  setPalette(pal);

  score = 0;

  hLayout1 = new QHBoxLayout();
  healthLayout = new QVBoxLayout();
  scoreLayout = new QVBoxLayout();
  weaponLayout = new QVBoxLayout();

  // add health info
  healthLabel = new QLabel("Health: 3");
  healthLabel->setFont(QFont("Fantasy", 32, QFont::Bold));
  healthLabel->setAlignment(Qt::AlignCenter);

  healthIconLabel = new QLabel();
  healthIconLabel->setPixmap(QPixmap(":/images/graphics/icons/statusbar/health.png").
                             scaled(64,64, Qt::KeepAspectRatio));
  healthIconLabel->setAlignment(Qt::AlignCenter);

  healthLayout->addWidget(healthIconLabel);
  healthLayout->addWidget(healthLabel);

  // add score info
  scoreLabel = new QLabel("Score: 0");
  scoreLabel->setFont(QFont("Fantasy", 32, QFont::Bold));
  scoreLabel->setAlignment(Qt::AlignCenter);

  scoreIconLabel = new QLabel();
  scoreIconLabel->setPixmap(QPixmap(":/images/graphics/icons/statusbar/star.png").
                             scaled(64,64, Qt::KeepAspectRatio));
  scoreIconLabel->setAlignment(Qt::AlignCenter);

  scoreLayout->addWidget(scoreIconLabel);
  scoreLayout->addWidget(scoreLabel);

  // add weapons info
  weaponLabel = new QLabel("Count: 50");
  weaponLabel->setFont(QFont("Fantasy", 32, QFont::Bold));
  weaponLabel->setAlignment(Qt::AlignCenter);

  QPixmap pixmap(":/images/graphics/missile/rocket-146109_640.png");
  QTransform transform;
  QTransform trans = transform.rotate(90);
  QPixmap transPixmap = QPixmap(pixmap.transformed(trans));

  weaponIconLabel = new QLabel();
  weaponIconLabel->setPixmap(transPixmap.scaled(200,200, Qt::KeepAspectRatio));
  weaponIconLabel->setAlignment(Qt::AlignCenter);

  weaponLayout->addWidget(weaponIconLabel);
  weaponLayout->addWidget(weaponLabel);

  hLayout1->addLayout(scoreLayout);
  hLayout1->addLayout(healthLayout);
  hLayout1->addLayout(weaponLayout);

  setLayout(hLayout1);

}

void Statusbar::increaseScore(int increment) {

  score += increment;
  scoreLabel->setText(QString("Score: ") + QString::number(score));

}
