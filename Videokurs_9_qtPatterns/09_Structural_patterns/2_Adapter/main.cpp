#include <QCoreApplication>

/*

  What
  Adapter pattern

  Description
  For after an implimentation has need developed
  Lets classes with incompatible interfaces work together

  Why
  Sometimes things change and you want to reuse old code
  Adapter makes things work after they're designed;

  Example
  Logger
  https://sourcemaking.com/design_patterns/adapter

 */

#include "filelogger.h"
#include "logadapter.h"



int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    QString message = "Hello from legacy system";
    FileLogger logger;

    //logger.write(message);

    LogAdapter adapter;
    adapter.setLogger(&logger);
    adapter.write("Hello new system");

    return a.exec();
}
