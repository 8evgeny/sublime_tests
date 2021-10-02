#ifndef MYCONNECTION_H
#define MYCONNECTION_H

#include <QObject>
#include <QRunnable>
#include <QTcpSocket>
#include <QDebug>
#include <QThread>

class MyConnection: public QRunnable
{
public:
    MyConnection();
    ~MyConnection();

    void run() override;

    qintptr handle() const;
    void setHandle(const qintptr &handle);

private:
    QTcpSocket *m_socket; //Has to be a pointer - QObject: Cannot create children for a parent that is in a different thread.
    qintptr m_handle;
    void handleConnection();

};

#endif // MYCONNECTION_H
