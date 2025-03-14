/*The single-responsibility principle (SRP) is a computer-programming principle that states
that every module, class or function in a computer program should have responsibility over a
single part of that program's functionality, and it should encapsulate that part. All of that module,
class or function's services should be narrowly aligned with that responsibility.*/

#include "tempconverter.h"
#include <QCoreApplication>
#include <QDebug>
#include <iostream>

int main(int argc, char* argv[])
{
    QCoreApplication a(argc, argv);

    TempConverter t;
    int value = 32;
//    qInfo() << "c to f" << t.celciusToFarengeit(value);
    std::cout << "c to f" << t.celciusToFarengeit(value) << std::endl;
//    qInfo() << "f to c" << t.farengeiyToCelcius(value);
    std::cout << "f to c" << t.farengeiyToCelcius(value) << std::endl;
//    return a.exec();
    a.exit(0);
}
