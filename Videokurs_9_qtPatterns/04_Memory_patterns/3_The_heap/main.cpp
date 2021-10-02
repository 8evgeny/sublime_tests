#include <QCoreApplication>

/*

  What
  The heap

  Description
  The "free store" where you can allocate anything you want
  BUT
  You control the memory managment

  Why
  Super fast access vs copying

  Example
  Pointer vs copy
  Copy is SLOW
  Pointers are FAST

 */

#include <QDebug>
#include "myclass.h"

void testCopy(MyClass object)
{
    qInfo() << &object << "len:" << object.data().length();
}

void testPointer(MyClass *object)
{
    //Whats happening here is C++ is giving us an object at the memory location
    object->log("Pointer");
    qInfo() << object << "Length: " << object->data().length();
}

void testAddressOf(MyClass &object)
{
    //Whats happening here is C++ is giving us an object at the memory location
    object.log("AddressOf");
    qInfo() << &object << "Length: " << object.data().length();
}

void testHeap()
{
    MyClass *myclass = new MyClass();
    myclass->log("Hello");

    delete myclass;
}

void testCopyPointer()
{
    MyClass *myclass = new MyClass();
    MyClass *myclass2;

    myclass->log("Hello");

    myclass2 = myclass; //COPY

    delete myclass;
}

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    MyClass m;
    //Test copy
    //testCopy(m);

    //testPointer(&m); //Basically same things

    //testAddressOf(m);

    //testHeap();

    testCopyPointer();

    return a.exec();
}
