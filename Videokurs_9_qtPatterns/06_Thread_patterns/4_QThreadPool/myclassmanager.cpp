#include "myclassmanager.h"

MyClassManager::MyClassManager(QObject *parent) : QObject(parent)
{

}

void MyClassManager::run()
{
    qInfo() << "Max Threads" << QThreadPool::globalInstance()->maxThreadCount();
    for(int  i = 0; i < 25; i++)
    {
        MyClass *myclass = new MyClass(nullptr); //no parent - on main thread
        myclass->setAutoDelete(false); //true will cause issues in this video

        myclass->setObjectName("MyClass" + QString::number(i));

        connect(myclass,&MyClass::started,this,&MyClassManager::started, Qt::QueuedConnection);
        connect(myclass,&MyClass::progress,this,&MyClassManager::progress, Qt::QueuedConnection);
        connect(myclass,&MyClass::finished,this,&MyClassManager::finished, Qt::QueuedConnection);

        QThreadPool::globalInstance()->start(myclass); //the apps global thread pool
    }


}

void MyClassManager::started()
{
    MyClass *myclass = qobject_cast<MyClass*>(sender());
    if(!myclass) return;

    //This is on the main thread!
    qInfo() << myclass << "Started slot" << QThread::currentThread();
}

void MyClassManager::finished()
{
    MyClass *myclass = qobject_cast<MyClass*>(sender());
    if(!myclass) return;

    //This is on the main thread!
    qInfo() << myclass << "Finished slot" << QThread::currentThread();

    //done with our object
    myclass->deleteLater(); //on the main thread
}

void MyClassManager::progress(int value)
{
    MyClass *myclass = qobject_cast<MyClass*>(sender());
    if(!myclass) return;

    //This is on the main thread!
    qInfo() << myclass << "Progress slot" << value << QThread::currentThread();
}
