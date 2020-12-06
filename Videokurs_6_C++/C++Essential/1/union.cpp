#include <iostream>
#include <string>

using namespace std;

struct A
{
    int a;
  union{
     int b;
     double c;
    };
};


union Container
{
    int int_field;
    double double_field;
};

typedef Container cnt;

int main()
{
    Container container;
    container.double_field = 0.5;

    A a;
a.a = 1;
    a.b = 2;

    A* a_ptr = &a;
    Container* cnt_ptr;

    a_ptr->a;
    cout << a_ptr->b;


    cout << a.b << "\n";
    cout << a.c << "\n";
    cout << "sizeof(A) "<<sizeof(A) << "\n";

    cout << "sizeof(container) " <<sizeof(container) << "\n";

    cout << container.int_field << "\n";
    cout << container.double_field << "\n";
    container = {4};

    cout << container.int_field << "\n";
    cout << container.double_field << "\n";
    return 0;
}
