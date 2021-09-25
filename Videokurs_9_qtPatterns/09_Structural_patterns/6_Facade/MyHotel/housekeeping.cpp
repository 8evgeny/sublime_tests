#include "housekeeping.h"

HouseKeeping::HouseKeeping(QObject *parent) : QObject(parent)
{

}

void HouseKeeping::clean(QString room)
{
    qInfo() << "Cleaning room" << room;
}
