#ifndef FILESYSTEM_H
#define FILESYSTEM_H

#include <QObject>
#include <QDebug>
#include <QFile>
#include <QTextStream>
#include "iFileIO.h"


class FileSystem : public QObject, public iFileIO
{
    Q_OBJECT
public:
    explicit FileSystem(QObject *parent = nullptr);

signals:


    // iFileIO interface
public:
    bool write(QString path, QString data);
    QString read(QString path);
};

#endif // FILESYSTEM_H
