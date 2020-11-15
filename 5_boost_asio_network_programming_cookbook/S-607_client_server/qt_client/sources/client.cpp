#include <QtWidgets>
#include <QtGui>
#include "client.h"
#include "INIReader.h"
constexpr char kConfigFile[] = "../config/config_client.ini";
QString img;
QString str_from_server;
QTime time_start;
bool response;
// ----------------------------------------------------------------------
MyClient::MyClient(const QString& strHost,
                   int            nPort,
                   QString imgname,
                   QWidget*       pwgt /*=0*/
                  ) : QWidget(pwgt)
                    , m_nNextBlockSize(0)
{
    img=imgname;
    m_pTcpSocket = new QTcpSocket(this);

//    m_pTcpSocket->setSocketOption(QAbstractSocket::LowDelayOption, 0);

    m_pTcpSocket->connectToHost(strHost, nPort);
    connect(m_pTcpSocket, SIGNAL(connected()), SLOT(slotConnected()));
    connect(m_pTcpSocket, SIGNAL(readyRead()), SLOT(slotReadyRead()));
    connect(m_pTcpSocket, SIGNAL(error(QAbstractSocket::SocketError)),
            this,         SLOT(slotError(QAbstractSocket::SocketError))
           );

    m_ptxtInfo  = new QTextEdit;
    m_ptxtInput = new QLineEdit;

    connect(m_ptxtInput, SIGNAL(returnPressed()),
            this,        SLOT(slotSendToServer())

           );
    m_ptxtInfo->setReadOnly(true);

    QPushButton* pcmd = new QPushButton("&Send");
    connect(pcmd, SIGNAL(clicked()), SLOT(slotSendToServer()));

    //Layout setup
    QVBoxLayout* pvbxLayout = new QVBoxLayout;
    pvbxLayout->addWidget(new QLabel("<H1>Client</H1>"));
    pvbxLayout->addWidget(m_ptxtInfo);
    pvbxLayout->addWidget(m_ptxtInput);
    pvbxLayout->addWidget(pcmd);
    setLayout(pvbxLayout);
}

// ----------------------------------------------------------------------

void MyClient::slotReadyRead()

{
    QDataStream in(m_pTcpSocket);
    in.setVersion(QDataStream::Qt_DefaultCompiledVersion);
    for (;;) {
        if (!m_nNextBlockSize) {
            if (m_pTcpSocket->bytesAvailable() < (int)sizeof(quint16)) {
                break;
            }
            in >> m_nNextBlockSize;
        }

        if (m_pTcpSocket->bytesAvailable() < m_nNextBlockSize) {
            break;
        }
        QTime   time_end;

                QString str;
        in >> time_end >> str_from_server;
        int msec = time_end.msecsSinceStartOfDay()-time_start.msecsSinceStartOfDay();
qDebug()<< str_from_server<<"start"<<time_start<<"finish"<<time_end<<"long(msec)"<<msec;

        m_nNextBlockSize = 0;

        m_ptxtInfo->append(time_end.toString() + " " + str_from_server);

    }
response=true;
}

// ----------------------------------------------------------------------
void MyClient::slotError(QAbstractSocket::SocketError err)
{
    QString strError =
        "Error: " + (err == QAbstractSocket::HostNotFoundError ?
                     "The host was not found." :
                     err == QAbstractSocket::RemoteHostClosedError ?
                     "The remote host is closed." :
                     err == QAbstractSocket::ConnectionRefusedError ?
                     "The connection was refused." :
                     QString(m_pTcpSocket->errorString())
                    );
    m_ptxtInfo->append(strError);
}


void MyClient::test(){
qDebug()<<QTime::currentTime();
    for(int i=0;i<5;++i){
        response=false;
    slotSendToServer();
while(1){
    if(response) break;
}
    }
qDebug()<<"end transfer files"<<QTime::currentTime();
}


// ----------------------------------------------------------------------
void MyClient::slotSendToServer()
{
    INIReader ini_reader(kConfigFile);
    auto debug_messages = ini_reader.GetBoolean("debug", "messages", true);

    QFile file;
    file.setFileName(img);
    file.open(QIODevice::ReadOnly);
    if(debug_messages)qDebug()<<"file_size "<<file.size();

    auto block_size_fo_transfer = ini_reader.GetInteger("transfer", "block", 32*1024);
    int number_part = file.size()/(block_size_fo_transfer*1024) + 1;

    if(debug_messages)qDebug()<<"parts_in_file"<<number_part;
    if(debug_messages)qDebug()<<"block_size"<<block_size_fo_transfer*1024;

    int current_part=0;//если 0 - передача служебной информации
    QByteArray barr;
    time_start = QTime::currentTime();
    while (1) {

    if(current_part !=0) {
     barr = file.read(block_size_fo_transfer*1024);
    if(barr.size()!=0)if(debug_messages)qDebug()<<"read part"<<current_part<<"size"<<barr.size();
     if (barr.size() ==0) break;
    }
    if(current_part ==0)if(debug_messages)qDebug()<<"creating service information";

    QByteArray  arrBlock;
    QDataStream out(&arrBlock, QIODevice::WriteOnly);
    out.setVersion(QDataStream::Qt_DefaultCompiledVersion);
    if(current_part !=0){
       out << quint16(0) <<  barr;
    if(debug_messages)qDebug()<<"sending part"<<current_part;
       out.device()->seek(0);
       out << quint16(arrBlock.size() -  sizeof(quint16));
    }
    if(current_part ==0){
        out << quint16(0) << int(number_part) << QTime::currentTime()<<QString(img);
    if(debug_messages)qDebug()<<"sending service information";
        out.device()->seek(0);
//        out << quint16(arrBlock.size() - sizeof(int) - sizeof(QString(img)));
        out << quint16(arrBlock.size() - sizeof(quint16));
    }
    ++current_part;
    m_pTcpSocket->write(arrBlock);
//m_pTcpSocket->flush();
     }
    file.close();
    m_ptxtInput->setText("");

}

// ------------------------------------------------------------------
void MyClient::slotConnected()
{
    m_ptxtInfo->append("Received the connected() signal");
}

