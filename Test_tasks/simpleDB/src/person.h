#pragma once
#include "simpleDB.h"
class Person {
public:
    Person(QString ,QString , unsigned ,unsigned , unsigned ,QString ,QDate );
    Person();
    ~Person();
    //имя, пол, возраст, рост, вес, национальность (выбор из внутреннего списка, например, подмножество https://tinyurl.com/q73okuc ),
    //    дата рождения,    дата смерти (может отсутствовать, ситуация должна быть корректно обработана).
    QString name;
    QString sex;
    unsigned age;
    unsigned growth;
    unsigned weight;
    QString nation;
    QDate bithday;
    QDate death;
private:
};
