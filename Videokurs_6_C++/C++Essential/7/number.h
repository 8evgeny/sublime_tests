#include <iostream>

using namespace std;

class Number
{
public:
    explicit Number(int data);

    Number& operator=(const Number& other);

    Number operator+(const Number& other) const;

    friend ostream& operator<<(ostream &s, const Number& number);

private:
    int data;
};
