#include <QCoreApplication>
#include <QThread>
#include <QDebug>
#include <QTimer>
#include <QSharedPointer>
#include "test.h"

//Creating and using threads

static QSharedPointer<QThread> sptr;
void timeout()
{
    if(!sptr.isNull())
    {
        qInfo() << "Time out - stopping other thread from:  " << QThread::currentThread();
        sptr.data()->quit();
    }

}

int main(int argc, char **argv)
{
    QCoreApplication a(argc, argv);

    qInfo() << "Application Thread: " << a.thread();
    qInfo() << "Current Thread: " << QThread::currentThread();

    test t;
    qInfo() << "Timer Thread: " << t.thread();

    QThread thread;
    sptr.reset(&thread);
    t.moveToThread(&thread);
    qInfo() << "Timer Thread: " << t.thread();

    t.start();
    qInfo() << "Thread Starter: " << thread.isRunning();

    thread.start();
    qInfo() << "Thread Starter: " << thread.isRunning();

    QTimer timer;
    timer.singleShot(5000, &timeout);

    return a.exec();
}
