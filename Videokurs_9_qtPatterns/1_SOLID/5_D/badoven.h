#ifndef BADOVEN_H
#define BADOVEN_H

#include <QObject>
#include <QDebug>
#include "basicoven.h"
#include "interfaces/IEvenHeat.h"

class BadOven : public BasicOven, public iEvenHeat
{
    Q_OBJECT
public:
    explicit BadOven(QObject *parent = nullptr);

signals:


    // iOven interface
public:
    void bake();

    // iEvenHeat interface
public:
    void flip();
    void rotate();
};

#endif // BADOVEN_H
