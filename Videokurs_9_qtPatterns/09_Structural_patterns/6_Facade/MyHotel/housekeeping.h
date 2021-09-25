#ifndef HOUSEKEEPING_H
#define HOUSEKEEPING_H

#include <QObject>
#include <QDebug>

class HouseKeeping : public QObject
{
    Q_OBJECT
public:
    explicit HouseKeeping(QObject *parent = nullptr);

    void clean(QString room);

signals:

};

#endif // HOUSEKEEPING_H
