#include <iostream>
#include <string>
#include "cat.h"
#include <typeinfo>
#include "number.h"

using namespace std;

uint Cat::vibr = 20;

class SomeClass;

class A
{
public:
    virtual void foo() = 0;
};

void A::foo()
{
    cout << "A::foo";
}

class B : public A
{
public:
    void foo() override;

    void new_method(SomeClass& some);

    int get_data(SomeClass& some);

private:
    string string_data;

    friend SomeClass;
};



class SomeClass
{
public:
    void get_string(B& b)
    {
        cout << b.string_data;
    }
private:
    int share_data()
    {
       return data;
    }
private:
    int data = 20;

    friend B;
    friend void B::new_method(SomeClass& some);
    friend void some_func(SomeClass& some);
};

void some_func(SomeClass& some)
{
    cout << __PRETTY_FUNCTION__ << endl;
    cout << some.data;
}

void B::foo()
{
    A::foo();
    cout << "B::foo";
}

int B::get_data(SomeClass& some)
{
    cout << some.share_data();
    return some.data;
}

void B::new_method(SomeClass& some)
{
    cout << some.share_data();
}

int main()
{
    Number a(4), b(10);

    b = a;

    cout << a + b;


//    B b;
//    SomeClass sm;
//    b.get_data(sm);
    return 0;
}
