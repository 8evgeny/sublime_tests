#include <QtCore>
#include <QImage>
#include <CL/cl.hpp>
#include "find_min_max.hpp"


QElapsedTimer eTimer;
quint64 timeSerial, timeParallel;


int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);
    Q_UNUSED(a)

    if (testEdge() != 0)
        return -1;

    return 0;
}


