#include "test.h"

test::test(QObject *parrent) : QObject(parrent)
{

}

void test::timeout()
{
    qInfo() << QDateTime::currentDateTime().toString() <<" on " <<QThread::currentThread() ;
}

void test::start()
{
    connect(&timer, &QTimer::timeout, this, &test::timeout);
    timer.setInterval(1000);
    timer.start();
}


