#include "airplane.h"

AirPlane::AirPlane(QObject *parent) : QObject(parent)
{

}

void AirPlane::refuel()
{
    qDebug() << this << "Refueling";
}

void AirPlane::fly()
{
    qDebug() << this << "Flying";
}

void AirPlane::land()
{
    qDebug() << this << "Land";
}
