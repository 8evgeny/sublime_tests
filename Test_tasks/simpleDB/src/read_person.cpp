#include "simpleDB.h"
#include "person.h"
using namespace std;
void read_person(Person & person,string name){
    QSettings settings(settingsFile, QSettings::IniFormat);
    settings.beginGroup("person");
    QString patch_to_DB = settings.value("patch_to_DB").toString();
    settings.endGroup();
//полный путь к файлу
    string path = patch_to_DB.toStdString()+"/"+name;
    ifstream file;
    file.open(path,ofstream::binary);
    if(!file.is_open()) cout<<"ошибка открытия файла\n";
    else{
        while(file.read((char*)&person, sizeof (Person)))

        cout<<"Данные успешно прочитаны из файла: "<< name<<"\n";
    }
    file.close();
}
