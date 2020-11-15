#include <QSettings>
#include <QApplication>
#include "client.h"
#include <iostream>
// ----------------------------------------------------------------------

int main(int argc, char** argv)
{
    QString imgname;
    int port;
    QString host;
    if(argc == 4) {
        host = QString(argv[1]);
        port = atoi(argv[2]);
        imgname=QString(argv[3]);
    }
    if(argc != 4) {
        host = "localhost";
        port=2323;
        imgname="test_img";
    }
    if(argc == 2) port = atoi(argv[1]);

    QApplication app(argc, argv);
    MyClient     client(host, port,imgname);
    client.show();

//    client.test();


    return app.exec();
}
