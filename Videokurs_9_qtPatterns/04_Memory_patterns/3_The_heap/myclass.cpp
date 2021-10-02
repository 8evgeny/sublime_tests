#include "myclass.h"

MyClass::MyClass()
{
    //We might break our system!
    // bad_alloc_error

    log("Constructing");

    qint64 limit = std::numeric_limits<qint64>::max();
    qint64 max = limit / 100000000000;
    for(qint64 i = 0; i < max; i++)
    {
        m_data.append('@'); //padd it with anything
    }
    log("Constructed");
}

MyClass::MyClass(const MyClass &old)
{
    log("Copy...");
    for(qint64 i = 0; i < old.data().length(); i++)
    {
        m_data.append(old.data().at(i)); //padd it with anything
    }
    log("Copied");
}

MyClass::~MyClass()
{
    log("Destroying");
    m_data.clear();
    log("Destructing");
}

QByteArray MyClass::data() const
{
    return m_data;
}

void MyClass::setData(const QByteArray &data)
{
    m_data = data;
}

void MyClass::log(QString message)
{
    qInfo() << QTime::currentTime().toString() << this << message;
}
