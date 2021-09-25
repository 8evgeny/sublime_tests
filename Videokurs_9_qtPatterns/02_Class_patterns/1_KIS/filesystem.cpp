#include "filesystem.h"

FileSystem::FileSystem(QObject *parent) : QObject(parent)
{

}


bool FileSystem::write(QString path, QString data)
{
    QFile file(path);
    if(!file.open(QIODevice::WriteOnly)) return false;

    QTextStream stream (&file);
    stream << data;
    file.close();
    return true;
}

QString FileSystem::read(QString path)
{
    QFile file(path);
    QString value;
    if(!file.open(QIODevice::ReadOnly)) return value;

    QTextStream stream (&file);
    value = stream.readAll();
    file.close();
    return value;
}
