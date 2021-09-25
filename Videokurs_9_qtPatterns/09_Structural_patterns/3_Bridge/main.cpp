#include <QCoreApplication>

/*

  What
  Bridge Design Pattern

  Description
  Decouple an abstraction from its implementation so that the two can vary independently.
  Note interfaces make this simple

  Why
  We want code reuse
  This is a design choice!
  Done BEFORE the orginal classes are created

  Example
  Logger with interfaces
  You have probably seem this dozens of times


 */

#include "interfaces/iLogger.h"

#include "simplelogger.h"
#include "advancedlogger.h"

void log(iLogger *logger)
{
    for(int i = 0; i < 5; i++)
    {
        logger->write("Item" + QString::number(i));
    }
}

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    SimpleLogger slog;
    AdvancedLogger alog;

    //log(&slog);
    log(&alog);


    return a.exec();
}
