#include <iostream>
#include <string>

using namespace std;

template <typename T>
T sum(T a, T b)
{
    return a + b;
}

template <typename T1, typename T2 = double>
auto sum(T1 a, T2 b) -> decltype(a + b)
{
    return a + b;
}

template <typename T = int>
class A
{
public:
    void process()
    {
        cout << a * 100 << endl;
    }

    T a;
};

template <>
class A<string>
{
public:
    void process()
    {
        cout << a + a << endl;
    }

    string a = "aba";
};

template <typename T>
class A<T*>
{
public:
    template<typename V>
    void process();

    T* a;
};

template <typename T>
template <typename V>
void A<T*>::process()
{
    cout << static_cast<V>(*a) << endl;
}


template <typename T, typename U>
class B : public A<T>
{
public:
    U b;
};

int main()
{
    cout << sum(4, 5) << endl;
    cout << sum(4.5, 6) << endl;
    cout << sum(4, "abcde") << endl;

    A<> object;
    object.a = 2.5;
    object.process();

    A<string> str;
    str.process();

    B<string, double> b;
    b.a = "str";
    b.process();

    double member = 15.5;
    A<double*> ptr;
    ptr.a = &member;
    ptr.process<double>();

    return 0;
}
