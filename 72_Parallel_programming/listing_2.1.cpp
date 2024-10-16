//стр 46
#include <thread>
#include <iostream>
void do_something(int& i)
{
    ++i;
    std::cout <<i<<std::endl;
}

struct func
{
    int& i;

    func(int& i_):i(i_){}

    void operator()()
    {
        for(unsigned j=0;j<1000000;++j)
        {
            do_something(i); //Потенциальный доступ к висячей ссылке
        }
    }
};


void oops()
{
    int some_local_state=0;
    func my_func(some_local_state); //не ждем завершения потока
    std::thread my_thread(my_func); //новый поток, возможно еще работает
    my_thread.detach();
}

int main()
{
    oops();
}
