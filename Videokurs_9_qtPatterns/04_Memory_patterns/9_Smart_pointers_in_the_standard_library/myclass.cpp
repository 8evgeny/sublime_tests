#include "myclass.h"

MyClass::MyClass(QObject *parent) : QObject(parent)
{
    qInfo() << this << "Constructed";
}

MyClass::~MyClass()
{
    qInfo() << this << "Destroyed";
}

void MyClass::test(QString value)
{
    qInfo() << this << value;
}
