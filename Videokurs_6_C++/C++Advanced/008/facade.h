#ifndef FACADE_H
#define FACADE_H

#include "meta_strategy.h"

class Alarm
{
public:
    void alarmOn();

    void alarmOff();
};

class Ac
{
public:
    void acOn();

    void acOff();
};

class Tv
{
public:
    void tvOn();

    void tvOff();
};

class HouseFacade
{
    Alarm alarm;
    Ac ac;
    Tv tv;

public:
    HouseFacade();

    void goToWork();

    void comeHome();
};

class ClientFacade : public MetaStrategy
{
public:
    ClientFacade() = default;

    void run() override;
};

#endif
