//Случайная передача за пределы защиты ссылки на защищаемые данные
#include <mutex>
#include <iostream>

class some_data
{
    int a;
    std::string b;
public:
    void do_something()
    {
        std::cout <<"unprotected data\n";
    }
};

class data_wrapper
{
private:
    some_data data;
    std::mutex m;
public:
    template<typename Function>
    void process_data(Function func)
    {
        std::lock_guard<std::mutex> l(m);
        func(data);
    }
};

some_data* unprotected;

void malicious_function(some_data& protected_data)
{
    unprotected=&protected_data;
}

data_wrapper x;

void foo()
{
    x.process_data(malicious_function);
    unprotected->do_something();
}

int main()
{
    foo();
}
