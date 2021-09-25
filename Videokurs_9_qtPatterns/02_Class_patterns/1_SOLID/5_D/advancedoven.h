#ifndef ADVANCEOVEN_H
#define ADVANCEOVEN_H

#include <QObject>
#include <QDebug>
#include "interfaces/iOven.h"
#include "interfaces/IEvenHeat.h"

class AdvanceOven : public QObject, public iEvenHeat, public iOven
{
    Q_OBJECT
public:
    explicit AdvanceOven(QObject *parent = nullptr);

signals:


    // iOven interface
public:
    void bake();

    // iEvenHeat interface
public:
    void flip();
    void rotate();
};

#endif // ADVANCEOVEN_H
