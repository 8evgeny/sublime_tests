#include "simpleDB.h"
using namespace std;
const QString DateTimeFormat = "dd.MM.yyyy hh:mm:ss";
const QString DateTimeFormat1 = "hh_mm_ss";

int main(int argc, char** argv) {
    const QString settingsFile = "configDB.ini";

    QSettings settings(settingsFile, QSettings::IniFormat);
    settings.beginGroup("nameDIR");
    QString patch_to_DB = settings.value("patch_to_DB").toString();



    return 0;
}



