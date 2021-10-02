#include <QCoreApplication>

/*

  What
  Memory leaks, stale pointers

  Description
  When we use a pointer, we are required to manage that memory

  Why
  its what makes C++ both powerfull and dangerous

  Examples
  Memory leak

 */

#include <QList>
#include <QDebug>
#include "myclass.h"

void fillList(QList<MyClass*> &list, int max)
{
    for(int i = 0 ; i < max; i++)
    {
        MyClass *myclass = new MyClass(); //We created, we OWN it
        myclass->setObjectName("Object " + QString::number(i));
        list.append(myclass);
    }

}

void demoLeak()
{
    qInfo() << "Making a leak";
    QList<MyClass*> list;
    fillList(list,5);

    list.clear();

    //None of the pointers have been deleted!!!
}

void demoDanglingPointer()
{
    qInfo() << "Making a dangling pointers";
    QList<MyClass*> list;
    fillList(list,5);

    //Delete some memory
    delete list.at(2); //memory is gone!

    qInfo() << list.length();

    foreach(MyClass *item, list)
    {
        qInfo() << item->objectName();
    }

}

void demoCorrect()
{
    qInfo() << "Making a pointers";
    QList<MyClass*> list;
    fillList(list,5);

    qDeleteAll(list); //Deletes the memory
    list.clear(); //Removes the dangling pointers

    qInfo() << list.length();

    foreach(MyClass *item, list)
    {
        qInfo() << item->objectName();
    }

}

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    //demoLeak();
    //demoDanglingPointer();

    demoCorrect();

    return a.exec();
}
