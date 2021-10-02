#include "myconnection.h"

MyConnection::MyConnection()
{
    qInfo() << this << "Constructed" << QThread::currentThread();
    //Do not create the socket - will cause an error
    //RAII???
}

MyConnection::~MyConnection()
{
    //Execution ends
    //Release the resources
    qInfo() << this << "Destroyed" << QThread::currentThread();
    if(m_socket)
    {
        if(m_socket->isOpen()) m_socket->close();
        delete m_socket;
    }
}


void MyConnection::run()
{
    //Execution starts!
    //Gather resources here

    qInfo() << this << "Running" << QThread::currentThread();

    m_socket = new QTcpSocket();
    m_socket->setSocketDescriptor(m_handle);
    m_socket->waitForConnected();
    handleConnection();

}

void MyConnection::handleConnection()
{
    qInfo() << this << "Handle Connection" << QThread::currentThread();
    QByteArray data;
    data.append("Hello World");
    m_socket->write(data);
    m_socket->waitForBytesWritten();
    m_socket->close(); //Don't hold the connection open longer than needed

    //At this point, the runnable has nothing running, and the thread pool deletes it!
}

qintptr MyConnection::handle() const
{
    return m_handle;
}

void MyConnection::setHandle(const qintptr &handle)
{
    m_handle = handle;
}


