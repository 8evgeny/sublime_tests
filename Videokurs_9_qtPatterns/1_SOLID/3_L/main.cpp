/*Liskov's notion of a behavioural subtype defines a notion of substitutability for objects; that is, if S
is a subtype of T, then objects of type T in a program may be replaced with objects of type S without altering
any of the desirable properties of that program*/


#include <QCoreApplication>
#include <QTcpSocket>
#include "mysocket.h"
#include <QDebug>

int main(int argc, char* argv[])
{
    QCoreApplication a(argc, argv);

//    QTcpSocket socket;
    MySocket socket;

    qInfo() << "Cconnection ...";
    socket.connectToHost("voidrealms.com",80);
    socket.waitForConnected();

    qInfo() << "Cconnected";
    // do someting while connected

    qInfo() << "Closing...";
    socket.close();
    if(socket.isOpen()) socket.waitForDisconnected();

    qInfo() << "Complete!";

    a.exit(0);
//    return a.exec();
}
