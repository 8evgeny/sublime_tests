#include "main.h"
#include "nativ.h"
void nativ::Qtvara(int argc, char** argv) {
  QApplication app(argc, argv);
  //  mtx.lock();

  QTableWidget tbl(2, 4);

  QTableWidgetItem* ptwi = 0;
  QStringList stolbVara, columVara;

  stolbVara << "Значение"
            << "Время"
            << "Название"
            << "Управитель";
  columVara << "Вара"
            << "Титхи";
  tbl.setHorizontalHeaderLabels(stolbVara);
  tbl.setVerticalHeaderLabels(columVara);

  //  int moonDay = 1; //Иногда улетает назад
  int moonDaystart = (int)tithi + 1;
  auto startTithi = findStartTithi(*this, moonDaystart);
  //  int moonDayend = 17;
  int moonDayend = (int)tithi + 1;
  auto endTithi = findEndTithi(*this, moonDayend);
  string time = startTithi.second.erase(5) + " " + endTithi.first.erase(5) +
                " - " + endTithi.second.erase(5) + " " +
                endTithi.second.erase(5);

  ptwi = new QTableWidgetItem(QString::fromStdString(to_string(vara)));
  tbl.setItem(0, 0, ptwi);
  ptwi = new QTableWidgetItem(QString::fromStdString(""));
  tbl.setItem(0, 1, ptwi);
  ptwi = new QTableWidgetItem(QString(QString::fromStdString(varaName)));
  tbl.setItem(0, 2, ptwi);
  ptwi = new QTableWidgetItem(QString(QString::fromStdString(varaLord)));
  tbl.setItem(0, 3, ptwi);

  ptwi = new QTableWidgetItem(QString::fromStdString(to_string(vara)));
  tbl.setItem(1, 0, ptwi);
  ptwi = new QTableWidgetItem(QString::fromStdString(time));
  tbl.setItem(1, 1, ptwi);
  ptwi = new QTableWidgetItem(QString(QString::fromStdString(varaName)));
  tbl.setItem(1, 2, ptwi);
  ptwi = new QTableWidgetItem(QString(QString::fromStdString(varaLord)));
  tbl.setItem(1, 3, ptwi);

  tbl.setColumnWidth(0, 100);
  tbl.setColumnWidth(1, 400);
  tbl.setColumnWidth(2, 200);
  tbl.setColumnWidth(3, 200);
  tbl.item(0, 0)->setTextAlignment(Qt::AlignHCenter);
  tbl.item(0, 1)->setTextAlignment(Qt::AlignHCenter);
  tbl.item(0, 2)->setTextAlignment(Qt::AlignHCenter);
  tbl.item(0, 3)->setTextAlignment(Qt::AlignHCenter);
  tbl.resize(1400, 120);
  tbl.setObjectName("  ");
  tbl.show();
  app.exec();
  //  mtx.unlock();
}
