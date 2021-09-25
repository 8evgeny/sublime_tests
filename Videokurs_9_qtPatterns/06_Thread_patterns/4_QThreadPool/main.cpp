#include <QCoreApplication>

/*

  What
  QThreadpool

  Description
  Mutliple threads automatically managed and reusable

  Why
  Less complex, and more effecient

  Example
  Threadpool

 */

#include <QThread>
#include "myclassmanager.h"

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    QThread::currentThread()->setObjectName("Main Thread");

    MyClassManager manager;
    manager.run();

    return a.exec();
}
