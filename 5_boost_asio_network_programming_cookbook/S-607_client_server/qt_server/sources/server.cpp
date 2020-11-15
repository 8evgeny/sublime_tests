#include <QtNetwork>
#include <QAbstractSocket>
#include <QtWidgets>
#include "server.h"
int current_part=0;
QString filename;
// ----------------------------------------------------------------------
MyServer::MyServer(int nPort, QWidget* pwgt /*=0*/) : QWidget(pwgt)
                                                    , m_nNextBlockSize(0)
{
    m_ptcpServer = new QTcpServer(this);

    if (!m_ptcpServer->listen(QHostAddress::Any, nPort)) {
        QMessageBox::critical(0,
                              "Server Error",
                              "Unable to start the server:"
                              + m_ptcpServer->errorString()
                             );
        m_ptcpServer->close();
        return;
    }
    connect(m_ptcpServer, SIGNAL(newConnection()),
            this,         SLOT(slotNewConnection())
           );

m_ptxt = new QTextEdit;
m_ptxt->setReadOnly(true);

//    Layout setup
    QVBoxLayout* pvbxLayout = new QVBoxLayout;
    pvbxLayout->addWidget(new QLabel("<H1>Server</H1>"));
    pvbxLayout->addWidget(m_ptxt);
    setLayout(pvbxLayout);
}

// ----------------------------------------------------------------------
/*virtual*/ void MyServer::slotNewConnection()
{
    QTcpSocket* pClientSocket = m_ptcpServer->nextPendingConnection();

    connect(pClientSocket, SIGNAL(disconnected()),
            pClientSocket, SLOT(deleteLater())
           );
    connect(pClientSocket, SIGNAL(readyRead()),
            this,          SLOT(slotReadClient())
           );

    sendToClient(pClientSocket, "Server Response: Connected!");
}

// ----------------------------------------------------------------------
void MyServer::slotReadClient()
{
    int all_part_in_file;

    QString filename_received;
    QFile file;


    QByteArray data_to_write;
    QTcpSocket* pClientSocket = (QTcpSocket*)sender();
    QDataStream in(pClientSocket);
    in.setVersion(QDataStream::Qt_DefaultCompiledVersion);
    for (;;) {
        if (!m_nNextBlockSize) {
            if (pClientSocket->bytesAvailable() < (int)sizeof(quint16)) {
                break;
            }
            in >> m_nNextBlockSize;
        }

        if (pClientSocket->bytesAvailable() < m_nNextBlockSize) {
            break;
        }

        QTime   time;
        QByteArray barr;

        if(current_part != 0) {
            in >> barr;
qDebug()<<"received part"<<current_part<<"size"<<barr.size();
            ++current_part;
            file.setFileName(filename);
            if(!file.isOpen())file.open(QIODevice::Append);
//            file.open(QIODevice::Append);
            file.write(barr);
            file.close();
        }

        if(current_part == 0) {
          in >> all_part_in_file >> time >> filename_received; //time - начало отправки файла
qDebug()<<"received service information";
          filename = "received_"+filename_received;
          ++current_part;
          file.setFileName(filename);
//          if(file.isOpen())file.close();
          file.open(QIODevice::WriteOnly);
          file.close();
          file.open(QIODevice::Append);
qDebug()<<"file"<<filename<<"in" << all_part_in_file<<"parts";
        }

        m_nNextBlockSize = 0;
        if(current_part == all_part_in_file+1) {
           sendToClient(pClientSocket, "server response: received file");
           QString strMessage = "Client has sent file " ;
           m_ptxt->append(time.toString() + " " + strMessage);
           current_part=0;
           }
    }
   file.close();
}

// ----------------------------------------------------------------------
void MyServer::sendToClient(QTcpSocket* pSocket, const QString& str)
{
    QByteArray  arrBlock;
    QDataStream out(&arrBlock, QIODevice::WriteOnly);
    out.setVersion(QDataStream::Qt_DefaultCompiledVersion);
    out << quint16(0) << QTime::currentTime() << str;

    out.device()->seek(0);
    out << quint16(arrBlock.size() - sizeof(quint16));

    pSocket->write(arrBlock);
}

