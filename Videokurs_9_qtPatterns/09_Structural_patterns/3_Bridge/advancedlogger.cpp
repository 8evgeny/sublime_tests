#include "advancedlogger.h"

AdvancedLogger::AdvancedLogger(QObject *parent) : QObject(parent)
{

}


void AdvancedLogger::write(QString message)
{
    QFile file("AdvancedLogger.txt");
    if(!file.open(QIODevice::Append))
    {
        qCritical() << file.errorString();
        return;
    }

    QString date = QDateTime::currentDateTime().toString();
    QString line;
    line.append(date);
    line.append(" - ");
    line.append(message);

    QTextStream stream(&file);
    stream << line << "\r\n";
    file.close();

    qInfo() << "Advanced Log:" << message;
}
