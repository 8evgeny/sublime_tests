#include "simpleDB.h"
#include "person.h"

 Person::Person(){};
 Person::Person (QString name,QString sex, unsigned age,unsigned growth, unsigned weight,QString nation,QDate bithday):
 name(name),sex(sex),age(age),growth(growth),weight(weight),nation(nation),bithday(bithday) {};
 Person::~Person(){};


