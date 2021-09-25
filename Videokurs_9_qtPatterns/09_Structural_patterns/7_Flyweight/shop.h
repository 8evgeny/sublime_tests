#ifndef SHOP_H
#define SHOP_H

#include <QObject>
#include <QDebug>
#include <QStringList>
#include <QThreadPool>
#include <QRandomGenerator>
#include "order.h"

class Shop : public QObject
{
    Q_OBJECT
public:
    explicit Shop(QObject *parent = nullptr);
    static void init();
    static void buy(int customer, int item);

    static QStringList menu;
signals:

};

#endif // SHOP_H
