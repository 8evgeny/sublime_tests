#include <iostream>
#include <thread>
#include <chrono>
using namespace  std;
//Лямбда выражения и возврат результата выполнения потока

int Sum(int a,int b){ //имя функции это указатель на функцию !!!
    this_thread::sleep_for(chrono::milliseconds(2000));
    cout<<"id_потока: " <<this_thread::get_id()<<" ========\t"<< "Sum STARTED\t========"<<endl;
    this_thread::sleep_for(chrono::milliseconds(5000));
    cout<<"id_потока: " <<this_thread::get_id()<<" ========\t"<< "Sum ENDED\t========"<<endl;
    return a + b;
}

int main(){
    int result;

//    auto lamb = [&result](){result = Sum(2,5);};
//    thread t(lamb);
    thread t([&result](){result = Sum(2,5);});

    for (int i = 0; i<10; ++i) { //непрерывная работа
        cout<< "id_потока: " <<this_thread::get_id()<<"\tmain works\t"<<i<<endl;
        this_thread::sleep_for(chrono::milliseconds(500));
    }

    t.join();
    cout<<"Sum result: "<<result<<endl;

    return 0;
}
