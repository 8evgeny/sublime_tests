#include <QCoreApplication>

/*
 What
 Smart pointers in the standard library

 Description
 Baked right into C++

 Why
 Just because Qt provides something doesn't mean its the best tool

 Example

 Test cases
 unique_ptr - only one object can point to it
 shared_ptr - multiple objects can point to it
 https://www.geeksforgeeks.org/smart-pointers-cpp/

 */

#include <QDebug>
#include <iostream>
#include <memory>
#include "myclass.h"

using namespace std;

void testUnique()
{
    qInfo() << "Testing Unique";
    unique_ptr<MyClass> p1(new MyClass());
    qInfo() << "p1=" << p1.get();

    p1->test("From pointer 1");

    unique_ptr<MyClass> p2 = move(p1); //take ownership
    qInfo() << "p1=" << p1.get(); //set to nullptr
    qInfo() << "p2=" << p2.get();

    //Test the pointers
    if(p1.get() != nullptr) p1->test("From pointer 1");
    if(p2.get() != nullptr) p2->test("From pointer 2");

}

void testShared()
{
    qInfo() << "Testing shared";
    shared_ptr<MyClass> p1(new MyClass());
    shared_ptr<MyClass> p2 = p1;

    qInfo() << "p1=" << p1.get();
    qInfo() << "p2=" << p2.get();

    //Test the pointers
    if(p1.get() != nullptr) p1->test("From pointer 1");
    if(p2.get() != nullptr) p2->test("From pointer 2");

    qInfo() << "Ref Count" << p1.use_count();
}

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    //testUnique();
    testShared();

    return a.exec();
}
