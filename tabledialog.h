#ifndef TABLEDIALOG_H
#define TABLEDIALOG_H

#include <QDialog>
#include <QPushButton>
#include <QLabel>
#include <QTableWidget>
#include <QTableWidgetItem>
#include <QVBoxLayout>
#include <QDebug>
#include <QList>

/**
 * @brief This is an example template for creating table dialogs.
 * @details Every dialog has two columns and a variable number of rows
 */
template <typename T1, typename T2, int rows>
class TableDialog : public QDialog {

public:
  /**
   * @brief TableDialog Constructor for dialog
   * @param listCol1 List of second column values
   * @param listCol2 List of first column values
   * @param title Dialog title
   * @param parent Parent widget
   */
  TableDialog(const T1 & listCol1, const T2 & listCol2,
              QStringList labels, QString title = "Table", QString intro = "",
              QWidget * parent = 0): QDialog(parent) {

    setWindowTitle(title);

    titleLabel = new QLabel(intro);
    table = new QTableWidget(rows, COLS_NUMBER);

    table->setHorizontalHeaderLabels(labels);

    // disable editing of table items
    table->setEditTriggers(QAbstractItemView::NoEditTriggers);

    qDebug() << listCol1;
    qDebug() << listCol2;

    // add column
    int i = 0;
    foreach (typename T1::value_type obj, listCol1) {
      table->setItem(i, 0, new QTableWidgetItem(QString("%1").arg(obj)));
      i++;
    }

    // add column
    i = 0;
    foreach (typename T2::value_type obj, listCol2) {
      table->setItem(i, 1, new QTableWidgetItem(QString("%1").arg(obj)));
      i++;
    }

    // resize Table Widget to fit contents
    table->resizeColumnsToContents();
    table->resizeRowsToContents();

    okButton = new QPushButton("OK");
    connect(okButton, SIGNAL(clicked(bool)), this, SLOT(accept()));

    QVBoxLayout * mainLayout = new QVBoxLayout();
    mainLayout->addWidget(titleLabel);
    mainLayout->addWidget(table);
    mainLayout->addWidget(okButton);

    setLayout(mainLayout);

  }

private:
  /**
   * @brief
   */
  enum {
    COLS_NUMBER = 2, ///< Number of columns
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
  QTableWidget  * table;

};

#endif // TABLEDIALOG_H
