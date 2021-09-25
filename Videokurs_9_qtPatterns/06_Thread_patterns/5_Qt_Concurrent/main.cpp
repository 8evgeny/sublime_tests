#include <QCoreApplication>

/*

  What
  Qt Concurrent

  Description
  High level threading

  Why
  Threads are complicated

  Example
  Folder Counter
  QT += concurrent

 */

#include <QDebug>
#include <QFileInfo>
#include <QTextStream>
#include <QThread>
#include "filescanner.h"

QString getPath()
{
    QTextStream stream(stdin);

    qInfo() << "Please enter a path:";
    QString value = stream.readLine();
    QFileInfo fi(value);
    if(!fi.exists())
    {
        qWarning() << "Not a valid path!";
        value.clear();
    }

    return value;
}


int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    QThread::currentThread()->setObjectName("Main Thread");

      QString path = getPath();
      while (path.isEmpty()) {
          path = getPath();
      }

      qInfo() << path;

      FileScanner fs;
      fs.scan(path);

    return a.exec();
}
