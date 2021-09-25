#ifndef ADVANCEDLOGGER_H
#define ADVANCEDLOGGER_H

#include <QObject>
#include <QDebug>
#include <QFile>
#include <QDateTime>
#include "interfaces/iLogger.h"

class AdvancedLogger : public QObject, public iLogger
{
    Q_OBJECT
public:
    explicit AdvancedLogger(QObject *parent = nullptr);

signals:


    // iLogger interface
public:
    void write(QString message) override;
};

#endif // ADVANCEDLOGGER_H
