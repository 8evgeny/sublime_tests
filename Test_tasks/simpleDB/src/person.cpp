#include "simpleDB.h"
#include "person.h"

 Person::Person(){
     live=true;};
 Person::Person (std::string name,
                std::string sex,
                unsigned age,
                unsigned growth,
                unsigned weight,
                std::string nation,
                QDate bithday):
 name(name),sex(sex),age(age),growth(growth),weight(weight),nation(nation),bithday(bithday) {};
 Person::~Person(){
     live=true;};

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

