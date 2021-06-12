#include <QCoreApplication>

/*The single-responsibility principle (SRP) is a computer-programming principle that states
that every module, class or function in a computer program should have responsibility over a
single part of that program's functionality, and it should encapsulate that part. All of that module,
class or function's services should be narrowly aligned with that responsibility.*/

#include "tempconverter.h"
#include <QDebug>

int main(int argc, char* argv[])
{
    QCoreApplication a(argc, argv);

    TempConverter t;
    int value = 32;
    qInfo() << "c to f" << t.celciusToFarengeit(value);
    qInfo() << "f to c" << t.farengeiyToCelcius(value);
    return a.exec();
}
