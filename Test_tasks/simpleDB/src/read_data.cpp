#include "simpleDB.h"
void read_data(){
    const QString settingsFile = "configDB.ini";
    QSettings settings(settingsFile, QSettings::IniFormat);
    settings.beginGroup("nameDIR");
    QString patch_to_DB = settings.value("patch_to_DB").toString();
    settings.endGroup();
    std::vector<std::string> v;
    QDir dirDB;
    dirDB.setPath(patch_to_DB);
    QStringList listFiles = dirDB.entryList(QDir::Files);
    fill_vector(listFiles, v);
    std::cout<<"БД содержит следующие записи:\n";
    print_vector(v);
};
