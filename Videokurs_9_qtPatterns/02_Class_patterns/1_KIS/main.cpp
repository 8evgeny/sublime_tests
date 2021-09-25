#include <QCoreApplication>
#include "iFileIO.h"
#include "filesystem.h"
#include <QDebug>
#include <QFile>
#include <QTextStream>

void testIO(iFileIO *io, QString path, QString data)
{
    if(io->write(path,data))
    {
        QString value = io->read(path);
        Q_ASSERT(data == value);
        qInfo() << "Complex IO test passed!";
    }
    else
    {
      qCritical() << "Complex IO test failed!";
    }
}

void complex(QString path, QString data)
{
    FileSystem fs;
    testIO(&fs, path, data);
}

void simple (QString path, QString data)
{
    QFile file(path);
    if(!file.open(QIODevice::ReadWrite))
    {
        qCritical() << "Simple test failed!";
        return;
    }
    QTextStream stream(&file);
    stream << data;
    stream.flush();
    stream.seek(0);

    QString value = stream.readAll();
    file.close();
    Q_ASSERT(value == data);
    qInfo() << "Simple IO test passed!";

}


int main(int argc, char* argv[])
{
    QCoreApplication a(argc, argv);
    QString path = "test.txt";
    QString data = "Hello world";

    complex(path, data);

    simple(path, data);

    a.exit(0);
//    return a.exec();
}
