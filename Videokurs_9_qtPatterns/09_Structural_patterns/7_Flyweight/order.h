#ifndef ORDER_H
#define ORDER_H

#include <QRunnable>
#include <QRandomGenerator>
#include <QDebug>
#include <QThread>
#include "shop.h"

class Order : public QRunnable
{
public:
    Order(int customer, int item);
    void run() override;
private:
    int m_customer;
    int m_item;
};

#endif // ORDER_H
