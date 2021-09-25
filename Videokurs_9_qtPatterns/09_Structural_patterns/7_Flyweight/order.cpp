#include "order.h"

Order::Order(int customer, int item)
{
    m_customer = customer;
    m_item = item;
}

void Order::run()
{
    qInfo() << "Starting order for customer" << m_customer;

    //Do stuff
    int value = QRandomGenerator::global()->bounded(1000);
    QThread::currentThread()->msleep(value);

    qInfo() << "Customer " << m_customer << " your order is ready " << Shop::menu.at(m_item);
}
