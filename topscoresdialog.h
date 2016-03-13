#ifndef TOPSCORESDIALOG_H
#define TOPSCORESDIALOG_H

#include <QDialog>

class QPushButton;
class QLabel;
class QTableWidget;

class TopScoresDialog : public QDialog {

public:
  TopScoresDialog(QWidget * parent = 0);

private:
  QString topScoreFileName;

  QPushButton * okButton;
  QLabel * titleLabel;
  QTableWidget * topScoresTable;

};

#endif // TOPSCORESDIALOG_H
