#include <QCoreApplication>

/*

  What
  Flyweight pattern

  Description
  Flyweight allows you to share bulky data that are common to each object.

  Why
  Sometimes you want to save resources

  Example
  Coffee Shop

 */

#include "shop.h"
#include <QDebug>
#include <QRandomGenerator>

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    Shop::init();
    qInfo() << "Total items: " << Shop::menu.length();

    int count = QRandomGenerator::global()->bounded(100);
    for(int customer = 0; customer < count; customer++)
    {
        int item = QRandomGenerator::global()->bounded(Shop::menu.length() - 1);
        Shop::buy(customer, item);
    }


    return a.exec();
}
