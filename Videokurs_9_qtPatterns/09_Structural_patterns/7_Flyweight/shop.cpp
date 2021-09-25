#include "shop.h"

QStringList Shop::menu = QStringList();

Shop::Shop(QObject *parent) : QObject(parent)
{

}

void Shop::init()
{
    qInfo() << "Building menu";
    for(int i = 0; i < 1000; i++)
    {
        menu.append("Menu Item " + QString::number(i));
    }
}

void Shop::buy(int customer, int item)
{
    Order *order = new Order(customer,item);
    order->setAutoDelete(true);
    QThreadPool::globalInstance()->start(order);
}
