#ifndef MYSOCKET_H
#define MYSOCKET_H

#include <QObject>
#include <QTcpSocket>
#include <QDebug>

class MySocket : public QTcpSocket
{
    Q_OBJECT
public:
    explicit MySocket(QObject *parent = nullptr);

signals:


    // QIODevice interface
public:
    void close();
};

#endif // MYSOCKET_H
