#include <QCoreApplication>

/*

  What
  The Stack

  Description
  C++ automatic memory managment
  Primarliy deals with scope
  This is basic C++

  Why
  C++ by design, the stack is how applications work

  Example
  In C++ the stack memory is where local variables get stored/constructed.
  The stack is also used to hold parameters passed to functions

  Find stack
  ulimit -s
  ulimit -a

  By design you can not copy or move a QObject
  QObjects are actually rather complex!
  QObjects usually communicate with each other using the signals and slots mechanism
  QObjects are organised in object trees.
  QObjects manages the memory of the children of a QObject

  https://doc.qt.io/qt-5/qobject.html#Q_DISABLE_COPY
  https://www.cleanqt.io/blog/why-qobject-subclasses-are-not-copyable

  Because of Q_DISABLE_COPY we are forced to use pointers or address of!

 */
#include "myclass.h"

/*
MyClass create()
{
    MyClass myclass;
    myclass.setObjectName("my class");
    return myclass;
}
*/

void testLifetime()
{
    MyClass myclass;
    myclass.setObjectName("my class");

}

void modClass(MyClass *myclass)
{
    myclass->setObjectName("my class");
    //myclass->deleteLater(); //anything on the stack should NOT be deleted!
}

void modRef(MyClass &myclass)
{
    myclass.setObjectName("my class");
    //myclass.deleteLater(); //anything on the stack should NOT be deleted!
}


int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    //testLifetime();

    MyClass myclass;
    //modClass(&myclass);

    modRef(myclass);

    return a.exec();
}
