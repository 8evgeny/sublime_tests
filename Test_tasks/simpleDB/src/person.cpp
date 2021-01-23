#include "simpleDB.h"
#include "person.h"

 Person::Person(){};
 Person::Person (std::string name,unsigned sex, unsigned age,unsigned growth, unsigned weight,std::string nation,QDate bithday):
 name(name),sex(sex),age(age),growth(growth),weight(weight),nation(nation),bithday(bithday) {};
 Person::~Person(){};


