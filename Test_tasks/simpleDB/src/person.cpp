#include "simpleDB.h"
#include "person.h"
using namespace std;
 Person::Person(){
     live=true;};
 Person::Person (string name,
                string sex,
                unsigned age,
                unsigned growth,
                unsigned weight,
                string nation,
                QDate bithday):
 name(name),sex(sex),age(age),growth(growth),weight(weight),nation(nation),bithday(bithday) {live=true;};
 Person::~Person(){};

 void Person::print(){
     std::cout
         <<"Имя: "<<name<<"\n"
         <<"Пол: "<<sex<<"\n"
         <<"Возраст: "<<age<<"\n"
         <<"Рост: "<<growth<<"\n"
         <<"Вес: "<<weight<<"\n"
         <<"Национальность: "<<nation<<"\n"
         <<"Дата рождения: "<<Person::bithday.toString().toStdString()<<"\n"
         <<"Дата смерти: "<<Person::death.toString().toStdString()<<"\n"
         <<"\n";
 }

 void Person::save_person(Person & person){
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

 void Person::read_person(string & name){
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
         while(file.read((char*)this, sizeof (Person)))

             cout<<"Данные успешно прочитаны из файла: "<< name<<"\n";
     }
     file.close();
 }
