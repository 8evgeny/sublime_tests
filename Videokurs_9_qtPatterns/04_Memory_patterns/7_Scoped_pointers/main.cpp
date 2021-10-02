#include <QCoreApplication>

/*

  What
  Scoped Pointers

  Description
  Automatically deleting when it goes out of scope

  Why
  Takes ownership of a pointer and automatically removes it

  Example
  QScopedPointer and QScopedArrayPointer

 */

#include <QDebug>
#include <QScopedPointer>
#include <QScopedArrayPointer>
#include "myclass.h"

MyClass *makeClass(QString name)
{
    //You would be suprised how many applications and libs do this
    return new MyClass(nullptr,name);
}

void testScoped()
{
    //Take ownership as soon as we get it!
    QScopedPointer<MyClass> p(makeClass("my smart pointer"));

    //COOOL
    p->test();

    //goes out of scope and everything is removed
}

void testScopedArray()
{
    //make an array of smart pointers
    int max = 10;
    QScopedArrayPointer<MyClass> p;
    p.reset(new MyClass[max]);

    for(int i = 0; i < max; i++)
    {
        p[i].test();
    }
    //goes out of scope and everything is removed
}

// this struct calls "myCustomDeallocator" to delete the pointer
struct SmartListCleanup
{
    static inline void cleanup(QList<MyClass*> *list)
    {
        qInfo() << "Custom Cleanup";
        qDeleteAll(*list);
        list->clear();
    }
};

void testCustomDelete()
{
    QList<MyClass*> list;
    QScopedPointer<QList<MyClass*>,SmartListCleanup> p(&list);

    for(int i = 0; i < 10; i++)
    {
        list.append(makeClass("List" + QString::number(i)));
    }

    //Do stuff with the list
    foreach(MyClass *item, list)
    {
        item->test();
    }

    //List automatically clears and deletes and pointers
}


int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    //testScoped();
    //testScopedArray();
    testCustomDelete();

    return a.exec();
}
