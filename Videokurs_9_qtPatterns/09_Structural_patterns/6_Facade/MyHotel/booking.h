#ifndef BOOKING_H
#define BOOKING_H

#include <QObject>
#include <QDebug>
#include <QRandomGenerator>

class Booking : public QObject
{
    Q_OBJECT
public:
    explicit Booking(QObject *parent = nullptr);
    void book(QString room);
    QString getRoom();
signals:

};

#endif // BOOKING_H
