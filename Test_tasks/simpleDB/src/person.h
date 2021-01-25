#pragma once
#include "simpleDB.h"
class Person {
public:
    Person(std::string ,std::string , unsigned ,unsigned , unsigned ,std::string ,QDate );
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
    bool live;
    void print();
    void save_person(Person &);
    void input_name();
    void input_sex();
    void input_bithday();
    void input_death();
//    void read_person(std::string &);
private:
};
