#include "number.h"

Number::Number(int data) : data(data)
{
}

Number& Number::operator=(const Number& other)
{
    if(this != &other)
    {
        data = other.data;
    }
    return *this;
}

Number Number::operator+(const Number &other) const
{
    return Number(data + other.data);
}

ostream& operator<<(ostream &s, const Number& number)
{
    s << "( " << number.data << " )" << endl;
    return s;
}
