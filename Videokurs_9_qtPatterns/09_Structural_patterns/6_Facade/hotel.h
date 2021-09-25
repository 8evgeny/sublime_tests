#ifndef HOTEL_H
#define HOTEL_H

#include <QObject>
#include <QDebug>
#include "interfaces/iHotel.h"
#include "MyHotel/bob.h"
#include "MyHotel/booking.h"
#include "MyHotel/housekeeping.h"

class Hotel : public QObject, public iHotel
{
    Q_OBJECT
public:
    explicit Hotel(QObject *parent = nullptr);

signals:


    // iHotel interface
public:
    void bookRoom() override;
};

#endif // HOTEL_H
