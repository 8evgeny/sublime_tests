#include <QtWidgets>
#include "server.h"
#include <iostream>
// ----------------------------------------------------------------------
int main(int argc, char** argv)
{
    int port=0;
    if(argc != 2) port=2323;
    std::cout<<port;
    if(argc == 2) port = atoi(argv[1]);
    QApplication app(argc, argv);
    MyServer     server(port);
//    server.show();

    return app.exec();
}

