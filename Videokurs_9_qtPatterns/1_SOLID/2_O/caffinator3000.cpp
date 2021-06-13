#include "caffinator3000.h"

caffinator3000::caffinator3000(QObject* parent)
    : QObject(parent)
{
}

void caffinator3000::addIngredients(QStringList& list)
{
    foreach (QString item, list) {
        qInfo() << "Adding" << item;
    }
}

void caffinator3000::brew()
{
    qDebug() << "Heating";
    marketing();
    qDebug() << "Pour";
    qDebug() << "Complete";
}

void caffinator3000::marketing()
{
    for (int i = 0; i < 10; ++i) {
        qDebug() << "Fire!!";
        qDebug() << "LOUD MUSIC!!!";
        qDebug() << "super-inject-cafffiiinnneee";
    }
}
