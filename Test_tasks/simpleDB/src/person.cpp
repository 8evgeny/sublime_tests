#include "simpleDB.h"
#include "person.h"
using namespace std;
 Person::Person(){
     live=true;};
// Person::Person (string name,
//                string sex,
//                unsigned age,
//                unsigned growth,
//                unsigned weight,
//                string nation,
//                QDate bithday):
// name(name),sex(sex),age(age),growth(growth),weight(weight),nation(nation),bithday(bithday) {live=true;};
 Person::~Person(){};

 void Person::print(){
     std::cout
         <<"1\tИмя: "<<name.toStdString()<<"\n"
         <<"2\tПол: "<<sex.toStdString()<<"\n"
         <<"3\tВозраст: "<<age<<"\n"
         <<"4\tРост: "<<growth<<"\n"
         <<"5\tВес: "<<weight<<"\n"
         <<"6\tНациональность: "<<nation.toStdString()<<"\n"
         <<"7\tДата рождения: "<<Person::bithday.toString().toStdString()<<"\n"
         <<"8\tДата смерти: "<<Person::death.toString().toStdString()<<"\n"
         <<"\n";
 }

 void Person::save_person(Person & person){
     QSettings settings(settingsFile, QSettings::IniFormat);
     settings.beginGroup("person");
     QString patch_to_DB = settings.value("patch_to_DB").toString();
     settings.endGroup();
     //полный путь к файлу
     string path = patch_to_DB.toStdString()+"/"+person.name.toStdString();
     fstream file;
     file.open(path, fstream::app | fstream::out | fstream::in | fstream::binary);
     if(!file.is_open()) cout<<"ошибка открытия файла\n";
     else{
//         int size = sizeof (person);
//         cout<<"размер: "<<size<<endl;
//         file.write((char*)&size, sizeof (int));
//         file.write((char*)&person, size);
//QString name;
//QString sex;
//unsigned age;
//unsigned growth;
//unsigned weight;
//QString nation;
//QDate bithday;
//QDate death;
//bool live;
const QString DateFormat = "dd/MM/yyyy";
        file<<person.name.toStdString()<<"\n";
        file<<person.sex.toStdString()<<"\n";
        file<<person.age<<"\n";
        file<<person.growth<<"\n";
        file<<person.weight<<"\n";
        file<<person.nation.toStdString()<<"\n";
        file<<person.bithday.toString(DateFormat).toStdString()<<"\n";
        if (!person.live) file<<person.death.toString(DateFormat).toStdString()<<"\n";
        if (person.live) file<<"no"<<"\n";
        file<<person.live<<"\n";
         cout<<"Данные успешно сохранены в файле: "<< person.name.toStdString()<<"\n";
     }
     file.close();
 }


