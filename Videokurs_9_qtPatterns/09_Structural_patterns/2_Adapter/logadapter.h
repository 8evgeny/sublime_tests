#ifndef LOGADAPTER_H
#define LOGADAPTER_H

#include <QObject>
#include <QDateTime>
#include <QDebug>
#include "filelogger.h"

class LogAdapter : public QObject
{
    Q_OBJECT
public:
    explicit LogAdapter(QObject *parent = nullptr);

    FileLogger *logger() const;
    void setLogger(FileLogger *logger);
    void write(QString message);
signals:


private:
    FileLogger *m_logger;

};

#endif // LOGADAPTER_H
