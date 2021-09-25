#include "logadapter.h"

LogAdapter::LogAdapter(QObject *parent) : QObject(parent)
{

}

FileLogger *LogAdapter::logger() const
{
    return m_logger;
}

void LogAdapter::setLogger(FileLogger *logger)
{
    m_logger = logger;
}

void LogAdapter::write(QString message)
{
    if(!m_logger)
    {
        qInfo() << "Please set the logger!";
        return;
    }

    QString current = QDateTime::currentDateTime().toString();
    QString newMessage = current + " " + message;

    m_logger->write(newMessage);
}
