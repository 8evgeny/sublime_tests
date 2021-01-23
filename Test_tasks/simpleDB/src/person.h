#pragma once
#include "simpleDB.h"
class Person {
public:
    Person(std::string ,unsigned , unsigned ,unsigned , unsigned ,std::string ,QDate );
    Person();
    ~Person();
    //имя, пол, возраст, рост, вес, национальность (выбор из внутреннего списка, например, подмножество https://tinyurl.com/q73okuc ),
    //    дата рождения,    дата смерти (может отсутствовать, ситуация должна быть корректно обработана).
    std::string name;
    unsigned sex;
    unsigned age;
    unsigned growth;
    unsigned weight;
    std::string nation;
    QDate bithday;
    QDate death;
private:
};
