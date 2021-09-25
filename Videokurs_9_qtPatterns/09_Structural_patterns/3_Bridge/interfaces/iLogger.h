#ifndef ILOGGER_H
#define ILOGGER_H

//the interface acts as a bridge

#include <QString>

class iLogger
{
public:
    virtual ~iLogger() {}
    virtual void write(QString message) = 0;
};

#endif // ILOGGER_H
