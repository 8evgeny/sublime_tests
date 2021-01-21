#include "simpleDB.h"
using namespace std;
const QString DateTimeFormat = "dd.MM.yyyy hh:mm:ss";
const QString DateTimeFormat1 = "hh_mm_ss";

int main(int argc, char** argv) {
 const QString settingsFile = "configDB.ini";
 QSettings settings(settingsFile, QSettings::IniFormat);
 settings.beginGroup("nameDIR");
 QString patch_to_DB = settings.value("patch_to_DB").toString();
 settings.endGroup();
 vector<string> v;
 QDir dirDB;
 dirDB.setPath(patch_to_DB);
 QStringList listFiles = dirDB.entryList(QDir::Files);
 fill_vector(listFiles, v);
 print_vector(v);












return 0;
}

void fill_vector(QStringList& listFiles, vector<string>& v) {
    for (auto& file : listFiles) {
        v.push_back(file.toStdString());
    }
}

void print_vector(vector<string>& v) {
    for (auto element : v)  cout<< element<<'\n';
}
