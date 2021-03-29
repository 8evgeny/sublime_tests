#include <QtWidgets>

#include "main.h"

int Qtvara(nativ& t, int argc, char** argv) {
  QApplication app(argc, argv);
  QTableWidget tbl(1, 3);

  QTableWidgetItem* ptwi = 0;
  QStringList stolbVara, columVara;

  stolbVara << "Значение"
            << "Название"
            << "Управитель";
  columVara << "Вара";
  tbl.setHorizontalHeaderLabels(stolbVara);
  tbl.setVerticalHeaderLabels(columVara);

  ptwi = new QTableWidgetItem(
      QString::fromStdString(to_string(t.vara)).arg(0).arg(0));
  tbl.setItem(0, 0, ptwi);
  ptwi = new QTableWidgetItem(
      QString(QString::fromStdString(t.varaName)).arg(0).arg(1));
  tbl.setItem(0, 1, ptwi);
  ptwi = new QTableWidgetItem(
      QString(QString::fromStdString(t.varaLord)).arg(0).arg(2));
  tbl.setItem(0, 2, ptwi);
  tbl.setColumnWidth(0, 100);
  tbl.setColumnWidth(1, 300);
  tbl.setColumnWidth(2, 160);
  tbl.item(0, 0)->setTextAlignment(Qt::AlignHCenter);
  tbl.item(0, 1)->setTextAlignment(Qt::AlignHCenter);
  tbl.item(0, 2)->setTextAlignment(Qt::AlignHCenter);
  tbl.resize(630, 60);
  tbl.setObjectName("  ");
  tbl.show();

  return app.exec();
}
