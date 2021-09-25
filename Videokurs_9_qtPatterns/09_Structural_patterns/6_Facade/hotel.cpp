#include "hotel.h"

Hotel::Hotel(QObject *parent) : QObject(parent)
{

}


void Hotel::bookRoom()
{
    Booking booking;
    HouseKeeping housekeeping;
    Bob lazybob;

    QString room = booking.getRoom();
    booking.book(room);

    for(int i = 0; i < 9; i++)
    {
        lazybob.fixit(room,"the sink");
    }

    housekeeping.clean(room);

    qInfo() << "Your room is ready:" << room;

}
