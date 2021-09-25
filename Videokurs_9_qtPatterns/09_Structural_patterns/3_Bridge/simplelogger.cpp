#include "simplelogger.h"

SimpleLogger::SimpleLogger(QObject *parent) : QObject(parent)
{

}


void SimpleLogger::write(QString message)
{
    QFile file("SimpleLogger.txt");
    if(!file.open(QIODevice::Append))
    {
        qCritical() << file.errorString();
        return;
    }

    QTextStream stream(&file);
    stream << message << "\r\n";
    file.close();

    qInfo() << "Simple Log:" << message;
}
