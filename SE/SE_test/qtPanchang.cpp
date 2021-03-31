#include "main.h"
#include "nativ.h"
void nativ::qtPanchang(int argc, char** argv) {
  QApplication app(argc, argv);
  //  mtx.lock();

  QTableWidget tbl(3, 6);
  tbl.setColumnWidth(0, 100);
  tbl.setColumnWidth(1, 300);
  tbl.setColumnWidth(2, 200);
  tbl.setColumnWidth(3, 200);
  tbl.setColumnWidth(4, 400);
  tbl.setColumnWidth(5, 500);
  tbl.setRowHeight(2, 260);
  //  tbl.setColumnWidth(7, 10);

  QTableWidgetItem* ptwi = 0;
  QStringList stolbVara, columVara;

  stolbVara << "Значение"
            << "Время"
            << "Название"
            << "Управитель"
            << "Божество"
            << "Результат";
  columVara << "Вара    "
            << "Титхи   "
            << "Накшатра:  ";
  tbl.setHorizontalHeaderLabels(stolbVara);

  tbl.setVerticalHeaderLabels(columVara);

  //  int moonDay = 1; //Иногда улетает назад
  int moonDay = (int)tithi + 1;
  auto startTithi = findStartTithi(*this, moonDay);
  auto endTithi = findEndTithi(*this, moonDay);
  string timeTithi = startTithi.first.erase(5) + " " +
                     startTithi.second.erase(5) + " - " +
                     endTithi.first.erase(5) + " " + endTithi.second.erase(5);
  int numNaksh = (int)naksh + 1;
  auto startNaksh = findStartNaksh(*this, numNaksh);
  auto endNaksh = findEndNaksh(*this, numNaksh);
  string timeNaksh = startNaksh.first.erase(5) + " " +
                     startNaksh.second.erase(5) + " - " +
                     endNaksh.first.erase(5) + " " + endNaksh.second.erase(5);

  ptwi = new QTableWidgetItem(QString::fromStdString(to_string(vara)));
  tbl.setItem(0, 0, ptwi);
  ptwi = new QTableWidgetItem(QString::fromStdString(""));
  tbl.setItem(0, 1, ptwi);
  ptwi = new QTableWidgetItem(QString(QString::fromStdString(varaName)));
  tbl.setItem(0, 2, ptwi);
  ptwi = new QTableWidgetItem(QString(QString::fromStdString(varaLord)));
  tbl.setItem(0, 3, ptwi);
  ptwi = new QTableWidgetItem(QString(QString::fromStdString("")));
  tbl.setItem(0, 4, ptwi);
  ptwi = new QTableWidgetItem(QString(QString::fromStdString("")));
  tbl.setItem(0, 5, ptwi);

  ptwi =
      new QTableWidgetItem(QString::fromStdString(to_string(tithi).erase(5)));
  tbl.setItem(1, 0, ptwi);
  ptwi = new QTableWidgetItem(QString::fromStdString(timeTithi));
  tbl.setItem(1, 1, ptwi);
  ptwi = new QTableWidgetItem(QString(QString::fromStdString(tithiName)));
  tbl.setItem(1, 2, ptwi);
  ptwi = new QTableWidgetItem(QString(QString::fromStdString(tithiLord)));
  tbl.setItem(1, 3, ptwi);
  ptwi = new QTableWidgetItem(QString(QString::fromStdString(tithiGod)));
  tbl.setItem(1, 4, ptwi);
  ptwi = new QTableWidgetItem(QString(QString::fromStdString(tithiResult)));
  tbl.setItem(1, 5, ptwi);

  ptwi =
      new QTableWidgetItem(QString::fromStdString(to_string(naksh).erase(5)));
  tbl.setItem(2, 0, ptwi);
  ptwi = new QTableWidgetItem(QString::fromStdString(timeNaksh));
  tbl.setItem(2, 1, ptwi);
  ptwi = new QTableWidgetItem(QString(QString::fromStdString(nakshName)));
  tbl.setItem(2, 2, ptwi);
  ptwi = new QTableWidgetItem(QString(QString::fromStdString(nakshLord)));
  tbl.setItem(2, 3, ptwi);
  ptwi = new QTableWidgetItem(QString(QString::fromStdString(nakshGod)));
  tbl.setItem(2, 4, ptwi);
  ptwi = new QTableWidgetItem(QString(QString::fromStdString(nakshResult)));
  tbl.setItem(2, 5, ptwi);

  tbl.item(0, 0)->setTextAlignment(Qt::AlignCenter);
  tbl.item(0, 1)->setTextAlignment(Qt::AlignCenter);
  tbl.item(0, 2)->setTextAlignment(Qt::AlignCenter);
  tbl.item(0, 3)->setTextAlignment(Qt::AlignCenter);
  tbl.item(0, 4)->setTextAlignment(Qt::AlignCenter);
  tbl.item(0, 5)->setTextAlignment(Qt::AlignLeft);
  tbl.item(1, 0)->setTextAlignment(Qt::AlignCenter);
  tbl.item(1, 1)->setTextAlignment(Qt::AlignCenter);
  tbl.item(1, 2)->setTextAlignment(Qt::AlignCenter);
  tbl.item(1, 3)->setTextAlignment(Qt::AlignCenter);
  tbl.item(1, 4)->setTextAlignment(Qt::AlignCenter);
  tbl.item(1, 5)->setTextAlignment(Qt::AlignLeft);
  tbl.item(2, 0)->setTextAlignment(Qt::AlignCenter);
  tbl.item(2, 1)->setTextAlignment(Qt::AlignCenter);
  tbl.item(2, 2)->setTextAlignment(Qt::AlignCenter);
  tbl.item(2, 3)->setTextAlignment(Qt::AlignCenter);
  tbl.item(2, 4)->setTextAlignment(Qt::AlignCenter);
  tbl.item(2, 5)->setTextAlignment(Qt::AlignLeft);

  tbl.resize(1850, 400);

  tbl.show();
  app.exec();
  //  mtx.unlock();
}
