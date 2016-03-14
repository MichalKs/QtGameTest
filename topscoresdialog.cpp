#include "topscoresdialog.h"
#include <QPushButton>
#include <QLabel>
#include <QTableWidget>
#include <QTableWidgetItem>
#include <QVBoxLayout>
#include <QDebug>

TopScoresDialog::TopScoresDialog(const QStringList & topScoreList, QWidget *parent):
  QDialog(parent) {

  topScoreFileName = "top.tsc";

  setWindowTitle("Top scores");

  titleLabel = new QLabel("Top scorers for the game:");
  topScoresTable = new QTableWidget(10, 2);

//  topScoresTable->setItem(0, 0, new QTableWidgetItem("Michal"));
//  topScoresTable->setItem(0, 1, new QTableWidgetItem("101"));

//  QList<QTableWidgetItem *> topScorersItems = topScoresTable->items();

  QStringList str;
  str << "Name" << "Score";
  topScoresTable->setHorizontalHeaderLabels(str);
//  topScoresTable->setDisabled(true);
//  topScoresTable->setFixedHeight(topScoresTable->sizeHint().height());
//  topScoresTable->setFixedWidth(topScoresTable->sizeHint().width());
//  topScoresTable->setViewportMargins(0,0,0,0);

//  QTableWidgetItem * item[2][10];

  int i = 0;
  foreach (QString player, topScoreList) {
    topScoresTable->setItem(i%10, 0, new QTableWidgetItem(player));
    i++;
  }

//  QString temp;
//  for (int i = 0; i < 2; i++) {
//    for (int j = 0; j < 10; j++) {
//      qDebug() << "Checking item " << j << " "<< i;
//      temp = QString("Item (%1,%2)").arg(j).arg(i);
//      topScoresTable->setItem(j, i, new QTableWidgetItem(temp));
//      item[i][j] = topScoresTable->itemAt(j,i);
//      if (item[i][j]) {
//        qDebug() << "item in non zero";
//        // FIXME Why the fuck doesn't this work?
//        item[i][j]->setFlags(Qt::NoItemFlags);
//        item[i][j]->setFont(QFont("Fantasy", 14, QFont::Bold));
//      }

//    }
//  }


  okButton = new QPushButton("OK");

  connect(okButton, SIGNAL(clicked(bool)), this, SLOT(accept()));

  QVBoxLayout * mainLayout = new QVBoxLayout();
  mainLayout->addWidget(titleLabel);
  mainLayout->addWidget(topScoresTable);
  mainLayout->addWidget(okButton);

  setLayout(mainLayout);

}
