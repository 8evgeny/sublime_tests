#pragma once
#include "simpleDB.h"
class Person {
public:
    Person(std::string ,std::string , unsigned ,unsigned , unsigned ,std::string ,QDate );
    Person();
    ~Person();
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
    void save_person();
    void read_person(std::string &);
    void input_name();
    void input_sex();
    void input_bithday();
    void input_death();
    void input_growth(int);
    void input_weight(int);
    void input_nation();
private:
};
