#include "myclass.h"

MyClass::MyClass(QObject *parent) : QObject(parent)
{
    qInfo() << this << "created";
}

MyClass::~MyClass()
{
    qInfo() << this << "destroyed";
}
