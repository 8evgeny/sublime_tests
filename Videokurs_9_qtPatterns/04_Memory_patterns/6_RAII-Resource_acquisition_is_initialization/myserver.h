#ifndef MYSERVER_H
#define MYSERVER_H

#include <QObject>
#include <QTcpServer>
#include <QThreadPool>
#include <QThread>
#include <QDebug>
#include "myconnection.h"

class MyServer : public QTcpServer
{
    Q_OBJECT
public:
    explicit MyServer(QObject *parent = nullptr);

signals:

public slots:
    void aboutToQuit();


protected:
    void incomingConnection(qintptr handle) override;
};

#endif // MYSERVER_H
