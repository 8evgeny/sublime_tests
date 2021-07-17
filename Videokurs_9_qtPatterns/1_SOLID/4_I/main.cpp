#include <QCoreApplication>
#include "interfaces/iFlying.h"
#include "interfaces/iMachine.h"
#include "bird.h"
#include "airplane.h"

void trip(iFlying *obj)
{
    obj->fly();
    obj->land();
}

void checkFuel(iMachine *obj)
{
    obj->refuel();
}

void testBird()
{
    Bird bird;
    trip(&bird);
}

void testPlane()
{
    AirPlane plane;
    trip(&plane);
    checkFuel(&plane);
}

int main(int argc, char* argv[])
{
    QCoreApplication a(argc, argv);
    testBird();
    testPlane();

    a.exit(0);
//    return a.exec();
}
