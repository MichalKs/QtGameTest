#include "statusbar.h"
#include <QLabel>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QGraphicsEffect>
#include <QPixmap>
#include <QTransform>
#include <QProgressBar>
#include <QPalette>

Statusbar::Statusbar(int initialHealth, int initialMissiles, QWidget * parent):
  QWidget(parent) {

  QPalette pal(palette());

  // set black background
  pal.setColor(QPalette::Background, Qt::black);
  setAutoFillBackground(true);
  setPalette(pal);

  score = 0;
  health = initialHealth;
  missileCount = initialMissiles;

  QHBoxLayout * hLayout1 = new QHBoxLayout();
  QVBoxLayout * healthLayout = new QVBoxLayout();
  QVBoxLayout * scoreLayout = new QVBoxLayout();
  QVBoxLayout * weaponLayout = new QVBoxLayout();

  // add health info
  healthLabel = new QLabel(QString("Health: ") + QString::number(health));
  healthLabel->setFont(QFont("Courier", 18, QFont::Bold));
  healthLabel->setAlignment(Qt::AlignCenter);

  healthIconLabel = new QLabel();
  healthIconLabel->setPixmap(QPixmap(":/images/graphics/icons/statusbar/health.png").
                             scaled(32,32, Qt::KeepAspectRatio));
  healthIconLabel->setAlignment(Qt::AlignCenter);

//  healthBar = new QProgressBar();
//  healthBar->setMaximum(health);
//  healthBar->setMinimum(0);
//  healthBar->setMaximumWidth(healthLabel->sizeHint().width());
//  healthBar->setValue(health);
//  healthBar->setFont(QFont("Courier", 14, QFont::Bold));
//  connect(this, SIGNAL(healthUpdated(int)), healthBar, SLOT(setValue(int)));

  healthLayout->addWidget(healthIconLabel);
//  healthLayout->addWidget(healthBar);
  healthLayout->addStretch();
  healthLayout->addWidget(healthLabel);

  // add score info
  scoreLabel = new QLabel("Score: 0");
  scoreLabel->setFont(QFont("Courier", 18, QFont::Bold));
  scoreLabel->setAlignment(Qt::AlignCenter);

  scoreIconLabel = new QLabel();
  scoreIconLabel->setPixmap(QPixmap(":/images/graphics/icons/statusbar/star.png").
                             scaled(32,32, Qt::KeepAspectRatio));
  scoreIconLabel->setAlignment(Qt::AlignCenter);

  scoreLayout->addWidget(scoreIconLabel);
  scoreLayout->addStretch();
  scoreLayout->addWidget(scoreLabel);

  // add weapons info
  weaponLabel = new QLabel(QString("Count: ")+QString::number(missileCount));
  weaponLabel->setFont(QFont("Courier", 18, QFont::Bold));
  weaponLabel->setAlignment(Qt::AlignCenter);

  QPixmap pixmap(":/images/graphics/missile/rocket-146109_640.png");
  QTransform transform;
  QTransform trans = transform.rotate(90);
  QPixmap transPixmap = QPixmap(pixmap.transformed(trans));

  weaponIconLabel = new QLabel();
  weaponIconLabel->setPixmap(transPixmap.scaled(100,100, Qt::KeepAspectRatio));
  weaponIconLabel->setAlignment(Qt::AlignCenter);

  weaponLayout->addWidget(weaponIconLabel);
  weaponLayout->addStretch();
  weaponLayout->addWidget(weaponLabel);

  hLayout1->addLayout(scoreLayout);
  hLayout1->addLayout(healthLayout);
  hLayout1->addLayout(weaponLayout);

//  setSizePolicy();

  setLayout(hLayout1);

}

void Statusbar::increaseScore(int increment) {
  score += increment;
  scoreLabel->setText(QString("Score: ") + QString::number(score));
}

void Statusbar::changeHealth(int h) {
  health = h;
  healthLabel->setText(QString("Health: ") + QString::number(health));
  emit healthUpdated(h);
}

void Statusbar::changeMissileCount(int c) {
  missileCount = c;
  weaponLabel->setText(QString("Count: ") + QString::number(missileCount));
}
