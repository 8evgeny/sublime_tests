#include "myclass.h"

MyClass::MyClass(QObject *parent) : QObject(parent)
{
    m_count = 0;
    qInfo()  << "Constructed" << "on" << QThread::currentThread();
}

MyClass::~MyClass()
{
    qInfo()  << "Final Count: " << m_count;
    qInfo()  << "Destroyed on:" << QThread::currentThread();
}

int MyClass::count() const
{
    return m_count;
}

void MyClass::addCount()
{
    QMutexLocker locker(&m_mutex);
    m_count++;
    qInfo()  << "count:" << m_count << "on" << QThread::currentThread();
}

QMutex *MyClass::mutex()
{
    return &m_mutex;
}
