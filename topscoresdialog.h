#ifndef TOPSCORESDIALOG_H
#define TOPSCORESDIALOG_H

#include <QDialog>

class QPushButton;
class QLabel;
class QTableWidget;

/**
 * @brief The TopScoresDialog class Dialog for displaying top scorers
 */
class TopScoresDialog : public QDialog {

public:
  TopScoresDialog(const QStringList & topScoreList, const QStringList & topScores,
                  QWidget * parent = 0);

private:
  QString topScoreFileName;

  QPushButton   * okButton;
  QLabel        * titleLabel;
  QTableWidget  * topScoresTable;

};

#endif // TOPSCORESDIALOG_H
