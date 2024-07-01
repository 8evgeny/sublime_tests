#include <QtCore>
#include <QImage>
#include <CL/cl.hpp>
#include "main.hpp"


QElapsedTimer eTimer;
quint64 timeSerial, timeParallel;


int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);
    Q_UNUSED(a)

//    if (testEdges() != 0)
//        return -1;

    if (testMatches() != 0)
        return -1;


    return 0;
}


