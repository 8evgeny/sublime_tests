#include "myserver.h"

MyServer::MyServer(QObject *parent) : QTcpServer(parent)
{

}

void MyServer::aboutToQuit()
{
    qInfo() << "Closing server";
    close();
}


void MyServer::incomingConnection(qintptr handle)
{
    //Make our runnable
    MyConnection *client = new MyConnection(); //DANGER, pointer with no parent!
    client->setHandle(handle); //Set the handle
    client->setAutoDelete(true); //Tell the thread pool to delete this when done

    QThreadPool::globalInstance()->start(client);//Start the runnable on the thread pool

}
