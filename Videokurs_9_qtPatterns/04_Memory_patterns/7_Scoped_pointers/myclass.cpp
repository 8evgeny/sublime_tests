#include "myclass.h"

MyClass::MyClass(QObject *parent, QString name) : QObject(parent)
{
    setObjectName(name);
    qInfo() << this << "Constructed";
}

MyClass::~MyClass()
{
    qInfo() << this << "Destroyed";
}

void MyClass::test()
{
    qInfo() << this << "test called";
}
