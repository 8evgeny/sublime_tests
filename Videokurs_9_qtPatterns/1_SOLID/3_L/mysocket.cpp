#include "mysocket.h"
#include <QDebug>

MySocket::MySocket(QObject *parent) : QTcpSocket(parent)
{

}

void MySocket::close()
{
   qInfo() << "Do somting before closing...";
   QTcpSocket::close();
}
