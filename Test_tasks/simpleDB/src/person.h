#pragma once
#include "simpleDB.h"
class Person {
public:
    Person(std::string ,std::string , unsigned ,unsigned , unsigned ,std::string ,QDate );
    Person();
    ~Person();
    //имя, пол, возраст, рост, вес, национальность (выбор из внутреннего списка, например, подмножество https://tinyurl.com/q73okuc ),
    //    дата рождения,    дата смерти (может отсутствовать, ситуация должна быть корректно обработана).
    std::string name;
    std::string sex;
    unsigned age;
    unsigned growth;
    unsigned weight;
    std::string nation;
    QDate bithday;
    QDate death;
    bool live;
    void print();
    void save_person(Person &);
    void read_person(Person & ,std::string &);
private:
};
