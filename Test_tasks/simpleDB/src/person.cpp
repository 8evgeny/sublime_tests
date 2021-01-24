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
         <<"Имя: "<<name.toStdString()<<"\n"
         <<"Пол: "<<sex.toStdString()<<"\n"
         <<"Возраст: "<<age<<"\n"
         <<"Рост: "<<growth<<"\n"
         <<"Вес: "<<weight<<"\n"
         <<"Национальность: "<<nation.toStdString()<<"\n"
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


