//#include "main.h"
#include <QApplication>
#include "appmaincontroller.h"
using namespace std;


int main(int argc, char** argv)
{
    QApplication a(argc, argv);
    AppMainController mc;

    a.exit(0);
}

// swedll.h:339:1: error: '__declspec' attributes are not enabled; use
// '-fdeclspec' or '-fms-extensions' to enable support for __declspec attributes
// swedll.h:74:30: note: expanded from macro 'DllImport'
