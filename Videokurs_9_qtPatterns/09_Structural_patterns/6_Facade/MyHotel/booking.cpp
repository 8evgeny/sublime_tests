#include "booking.h"

Booking::Booking(QObject *parent) : QObject(parent)
{

}

void Booking::book(QString room)
{
    qInfo() << "Booking room" << room;
}

QString Booking::getRoom()
{
    int room = QRandomGenerator::global()->bounded(1,100);
    return QString::number(room);
}
