#include "facade.h"
#include <iostream>

using namespace std;

void Alarm::alarmOn()
{
    cout << "Alarm is on and house is secured" << endl;
}

void Alarm::alarmOff()
{
    cout << "Alarm is off and you can go into the house" << endl;
}

void Ac::acOn()
{
    cout << "Ac is on" << endl;
}

void Ac::acOff()
{
    cout << "AC is off" << endl;
}

void Tv::tvOn()
{
    cout << "Tv is on" << endl;
}

void Tv::tvOff()
{
    cout << "TV is off" << endl;
}

HouseFacade::HouseFacade() {}

void HouseFacade::goToWork()
{
    ac.acOff();
    tv.tvOff();
    alarm.alarmOn();
}

void HouseFacade::comeHome()
{
    alarm.alarmOff();
    ac.acOn();
    tv.tvOn();
}

void ClientFacade::run()
{
    HouseFacade hf;

    // Rather than calling 100 different on and off functions thanks to facade I only have 2
    // functions...
    hf.goToWork();
    hf.comeHome();
}
