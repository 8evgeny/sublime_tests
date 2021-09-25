#ifndef BASICOVEN_H
#define BASICOVEN_H

#include <QObject>
#include <QDebug>
#include "interfaces/iOven.h"

class BasicOven : public QObject, public iOven
{
    Q_OBJECT
public:
    explicit BasicOven(QObject *parent = nullptr);

signals:


    // iOven interface
public:
    void bake();
};

#endif // BASICOVEN_H
