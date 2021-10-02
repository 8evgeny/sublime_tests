#include "myrunnable.h"

MyRunnable::MyRunnable()
{

}


void MyRunnable::run()
{
    for(int i = 0; i < 10; i++)
    {
        //Sim long activity
        int ms = QRandomGenerator::global()->bounded(0,500);
        QThread::currentThread()->msleep(ms);

        m_pointer->addCount();
    }
}

QSharedPointer<MyClass> MyRunnable::pointer() const
{
    return m_pointer;
}

void MyRunnable::setPointer(const QSharedPointer<MyClass> &pointer)
{
    m_pointer = pointer;
}
