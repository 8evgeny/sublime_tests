#ifndef FILELOGGER_H
#define FILELOGGER_H

//This is our legacy logging class

#include <QObject>
#include <QFile>
#include <QTextStream>
#include <QDebug>

class FileLogger : public QObject
{
    Q_OBJECT
public:
    explicit FileLogger(QObject *parent = nullptr);

    void write(QString message);

signals:

};

#endif // FILELOGGER_H
