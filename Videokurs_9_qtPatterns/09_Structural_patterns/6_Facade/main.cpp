#include <QCoreApplication>

/*

  What
  Facade

  Description
  Facade defines a higher-level interface that makes the subsystem easier to use.

  Why
  make life easier

  Example
  Hotel
  Make MyHotel classes
  Add an interface
  Make the Facade


 */

#include "hotel.h"

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    Hotel hotel;
    hotel.bookRoom();


    return a.exec();
}
