#include "caffinator3000.h"
#include <iostream>
using std::cout;
using std::endl;

caffinator3000::caffinator3000(QObject* parent)
    : QObject(parent)
{
}

void caffinator3000::addIngredients(QStringList& list)
{
    foreach (QString item, list) {
//        qInfo() << "Adding" << item;
        cout << "Adding " << item.toStdString() <<endl;
    }
}

void caffinator3000::brew()
{
//    qDebug() << "Heating";
    cout << "Heating" <<endl;
    marketing();
//    qDebug() << "Pour";
    cout << "Pour" <<endl;
//    qDebug() << "Complete";
    cout << "Complete" <<endl;
}

void caffinator3000::marketing()
{
    for (int i = 0; i < 10; ++i) {
//        qDebug() << "Fire!!";
        cout << "Fire!!" <<endl;
//        qDebug() << "LOUD MUSIC!!!";
        cout << "LOUD MUSIC!!!" <<endl;
//        qDebug() << "super-inject-cafffiiinnneee";
        cout << "super-inject-cafffiiinnneee" <<endl;
    }
}
