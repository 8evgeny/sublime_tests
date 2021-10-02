#include <QCoreApplication>
/*

  What
  Shared Pointers

  Description
  Pointers that auto-delete when no longer used AND can be used more than once

  Why
  Sometimes multiple things point to the same pointer

  Example
  QSharedPointer
  QSharedPointer will delete the pointer it is holding when it goes out of scope,
  provided no other QSharedPointer objects are referencing it.
  Reference counting
  Also not thread safe as the references might be on different threads

  There is probably a better example out there
  We are focused on QSharedPointer, not so much threads

 */

#include <QDebug>
#include <QThread>
#include <QThreadPool>
#include <QSharedPointer>
#include "myclass.h"
#include "myrunnable.h"

void test()
{
    qInfo() << "******** Entering test";

    QSharedPointer<MyClass> ptr(new MyClass);
    for(int i = 0; i < QThreadPool::globalInstance()->maxThreadCount(); i++)
    {
        MyRunnable *runnable = new MyRunnable();
        runnable->setAutoDelete(true);
        runnable->setPointer(ptr);
        QThreadPool::globalInstance()->start(runnable);

    }

    qInfo() << "******** Exiting test";
}

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    test();

    return a.exec();
}
