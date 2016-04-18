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
  /**
   * @brief TopScoresDialog Constructor for dialog
   * @param topScoreList List of top scorers' names
   * @param topScores List of top scores
   * @param parent Parent widget
   */
  TopScoresDialog(const QStringList & topScoreList, const QStringList & topScores,
                  QWidget * parent = 0);

private:
  /**
   * @brief Private constants
   */
  enum {
    ROWS_NUMBER = 10, ///< Number of rows
    COLS_NUMBER = 2,  ///< Number of columns
  };
  /**
   * @brief okButton OK button
   */
  QPushButton   * okButton;
  /**
   * @brief titleLabel Label
   */
  QLabel        * titleLabel;
  /**
   * @brief topScoresTable Table widget for displaying top scores
   */
  QTableWidget  * topScoresTable;

};

#endif // TOPSCORESDIALOG_H
