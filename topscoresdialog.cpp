#include "topscoresdialog.h"
#include <QPushButton>
#include <QLabel>
#include <QTableWidget>
#include <QTableWidgetItem>
#include <QVBoxLayout>
#include <QDebug>

TopScoresDialog::TopScoresDialog(const QStringList & topScoreList,
                                 const QStringList & topScores,
                                 QWidget *parent): QDialog(parent) {


  setWindowTitle("Top scores");

  titleLabel = new QLabel("Top scorers for the game:");
  topScoresTable = new QTableWidget(ROWS_NUMBER, COLS_NUMBER);

  QStringList str;
  str << "Name" << "Score";
  topScoresTable->setHorizontalHeaderLabels(str);

  // disable editing of table items
  topScoresTable->setEditTriggers(QAbstractItemView::NoEditTriggers);

  qDebug() << "Top scores:\n";
  qDebug() << topScoreList;
  qDebug() << topScores;

  // add names
  int i = 0;
  foreach (QString player, topScoreList) {
    topScoresTable->setItem(i%10, 0, new QTableWidgetItem(player));
    i++;
  }

  // add scores
  i = 0;
  foreach (QString score, topScores) {
    topScoresTable->setItem(i%10, 1, new QTableWidgetItem(score));
    i++;
  }

  // resize Table Widget to fit contents
  topScoresTable->resizeColumnsToContents();
  topScoresTable->resizeRowsToContents();

  okButton = new QPushButton("OK");
  connect(okButton, SIGNAL(clicked(bool)), this, SLOT(accept()));

  QVBoxLayout * mainLayout = new QVBoxLayout();
  mainLayout->addWidget(titleLabel);
  mainLayout->addWidget(topScoresTable);
  mainLayout->addWidget(okButton);

  setLayout(mainLayout);

}
