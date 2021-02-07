#include <iostream>
#include <thread>
#include <chrono>
using namespace  std;
//Потоки и методы класса

class MyClass
{
    public:
    void DoWork()
    {
        this_thread::sleep_for(chrono::milliseconds(2000));
        cout<<"id_потока: " <<this_thread::get_id()<<" ========\t"<< "DoWork STARTED\t========"<<endl;
        this_thread::sleep_for(chrono::milliseconds(5000));

        cout<<"id_потока: " <<this_thread::get_id()<<" ========\t"<< "DoWork ENDED\t========"<<endl;
    }
    void DoWork2(int a)
    {
        this_thread::sleep_for(chrono::milliseconds(2000));
        cout<<"id_потока: " <<this_thread::get_id()<<" ========\t"<< "DoWork2 STARTED\t========"<<endl;
        this_thread::sleep_for(chrono::milliseconds(5000));
        cout<<"Параметр: " <<a<<endl;
        cout<<"id_потока: " <<this_thread::get_id()<<" ========\t"<< "DoWork2 ENDED\t========"<<endl;
    }
    int Sum(int a,int b){
        this_thread::sleep_for(chrono::milliseconds(2000));
        cout<<"id_потока: " <<this_thread::get_id()<<" ========\t"<< "Sum STARTED\t========"<<endl;
        this_thread::sleep_for(chrono::milliseconds(5000));
        cout<<"id_потока: " <<this_thread::get_id()<<" ========\t"<< "Sum ENDED\t========"<<endl;
        return a + b;
    }

};

int main(){
    int result;
    MyClass m;

//    thread t([&result,&m](){ // Передаем 2 переменные
    thread t([&](){ // Передаем все переменные
    result = m.Sum(2,5);
    });
    thread t1(&MyClass::DoWork,m);
    thread t2(&MyClass::DoWork2,m,5);
    for (int i = 1; i<=10; ++i) { //непрерывная работа
        cout<< "id_потока: " <<this_thread::get_id()<<"\tmain works\t"<<i<<endl;
        this_thread::sleep_for(chrono::milliseconds(1000));
    }

    t.join();
    t1.join();
    t2.join();
    cout<<"Sum result: "<<result<<endl;
    return 0;
}
