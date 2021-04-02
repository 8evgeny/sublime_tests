#include "main.h"
#include "nativ.h"
void nativ::qtPanchang(nativ& nativ) {
  string nav = nativ.navatara(*this);

  int argc = 1;
  char* argv[1];
  string arg0 = "./test";
  argv[0] = (char*)arg0.c_str();
  QApplication app(argc, argv);
  //  mtx.lock();

  QTableWidget tbl(6, 6);
  tbl.setColumnWidth(0, 100);
  tbl.setColumnWidth(1, 300);
  tbl.setColumnWidth(2, 200);
  tbl.setColumnWidth(3, 200);
  tbl.setColumnWidth(4, 400);
  tbl.setColumnWidth(5, 500);
  tbl.setRowHeight(2, 260);
  tbl.resizeRowsToContents();

  QTableWidgetItem* ptwi = 0;
  QStringList row, colum;

  row << "Значение"
      << "Время"
      << "Название"
      << "Управитель"
      << "Божество"
      << "Результат";
  colum << "Вара    "
        << "Титхи   "
        << "Накшатра:  "
        << "Карана"
        << "Йога"
        << "Наватара";
  tbl.setHorizontalHeaderLabels(row);

  tbl.setVerticalHeaderLabels(colum);

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

  auto startKarana = findStartKarana(*this);
  auto endKarana = findEndKarana(*this);
  string timeKarana =
      startKarana.first.erase(5) + " " + startKarana.second.erase(5) + " - " +
      endKarana.first.erase(5) + " " + endKarana.second.erase(5);

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

  ptwi = new QTableWidgetItem(QString::fromStdString(to_string(karana)));
  tbl.setItem(3, 0, ptwi);
  ptwi = new QTableWidgetItem(QString::fromStdString(timeKarana));
  tbl.setItem(3, 1, ptwi);
  ptwi = new QTableWidgetItem(QString(QString::fromStdString(karanaName)));
  tbl.setItem(3, 2, ptwi);
  ptwi = new QTableWidgetItem(QString(QString::fromStdString(karanaLord)));
  tbl.setItem(3, 3, ptwi);
  ptwi = new QTableWidgetItem(QString(QString::fromStdString(karanaGod)));
  tbl.setItem(3, 4, ptwi);
  ptwi = new QTableWidgetItem(QString(QString::fromStdString(karanaResult)));
  tbl.setItem(3, 5, ptwi);

  ptwi = new QTableWidgetItem(QString::fromStdString(nativ.name));
  tbl.setItem(5, 2, ptwi);
  ptwi = new QTableWidgetItem(QString::fromStdString(nav));
  tbl.setItem(5, 5, ptwi);

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
  tbl.item(3, 0)->setTextAlignment(Qt::AlignCenter);
  tbl.item(3, 1)->setTextAlignment(Qt::AlignCenter);
  tbl.item(3, 2)->setTextAlignment(Qt::AlignCenter);
  tbl.item(3, 3)->setTextAlignment(Qt::AlignCenter);
  tbl.item(3, 4)->setTextAlignment(Qt::AlignCenter);
  tbl.item(3, 5)->setTextAlignment(Qt::AlignLeft);
  tbl.item(5, 2)->setTextAlignment(Qt::AlignCenter);

  tbl.resize(1850, 400);

  tbl.show();
  app.exec();
  //  mtx.unlock();
}
