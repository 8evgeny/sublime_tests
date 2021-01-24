#include "simpleDB.h"
#include "person.h"
using namespace std;
void save_person(Person & person){
 QSettings settings(settingsFile, QSettings::IniFormat);
 settings.beginGroup("person");
 QString patch_to_DB = settings.value("patch_to_DB").toString();
 settings.endGroup();
//полный путь к файлу
 string path = patch_to_DB.toStdString()+"/"+person.name;
 ofstream file;
 file.open(path,ofstream::binary);
 if(!file.is_open()) cout<<"ошибка открытия файла\n";
 else{
 file.write((char*)&person, sizeof (Person));
 cout<<"Данные успешно сохранены в файле: "<< person.name<<"\n";
 }
 file.close();
}
