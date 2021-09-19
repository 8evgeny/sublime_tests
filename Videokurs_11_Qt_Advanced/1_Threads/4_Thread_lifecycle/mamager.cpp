#include "manager.h"

manager::manager(QObject *parent) : QObject(parent)
{
    for(int i = 0;i < 5;i++)
    {
        QThread* thread = new QThread(this);
        thread->setObjectName("Thread " + QString::number(i));
        qInfo() << "Created: " << thread->objectName();

        connect(thread,&QThread::started, this, &manager::started);
        connect(thread,&QThread::finished, this, &manager::finished);

        threads.append(thread);
    }
}

void manager::start()
{
    qInfo() << "Starting...";

    foreach(QThread* thread, threads)
    {
        qInfo() << "Starting: " << thread->objectName();
        counter* c = new counter(); //NO PARENT!!!!
        c->moveToThread(thread);
        //c->start(); //Single Thread!!!

        connect(thread,&QThread::started, c,&counter::start);
        thread->start();
    }
}

void manager::started()
{
    QThread* thread = qobject_cast<QThread*>(sender());
    if(!thread) return;
    qInfo() << "Started: " << thread->objectName();
}

void manager::finished()
{
    QThread* thread = qobject_cast<QThread*>(sender());
    if(!thread) return;
    qInfo() << "Finished: " << thread->objectName();
}
