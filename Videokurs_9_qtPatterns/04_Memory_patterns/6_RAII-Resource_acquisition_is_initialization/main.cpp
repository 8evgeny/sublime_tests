#include <QCoreApplication>

/*

  What
  RAII - Resource Acquisition Is Initialization
  https://en.cppreference.com/w/cpp/language/raii
  https://en.wikipedia.org/wiki/Resource_acquisition_is_initialization

  Description
  Resource allocation is done during object creation, by the constructor,
  While resource deallocation is done during object destruction, by the destructor.

  Why
  Makes it easier, and more stable
  Qt follows this (mostly)

  Example
  Simple server
  If you are not following RAII, you have to ask yourself WHY
  Are you doing a bad design pattern
  Is there is better way to do what you are attempting
  QTCPServer with a thread pool is an example of how its easy to break from this

  QT += network
 */

#include <QObject>
#include "myserver.h"

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    MyServer server;
    QObject::connect(&a,&QCoreApplication::aboutToQuit,&server,&MyServer::aboutToQuit);
    if(!server.listen(QHostAddress::Any,3372))
    {
        qCritical() << server.errorString();
    }
    if(server.isListening()) qInfo() << "Listening";

    return a.exec();
}



