#include "myclass.h"

MyClass::MyClass(QObject *parent) : QObject(parent)
{
    qInfo() << this << "Constructed";
}

MyClass::~MyClass()
{
    qInfo() << this << "Destroyed";
}
