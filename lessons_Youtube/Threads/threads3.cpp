#include <iostream>
#include <thread>
#include <chrono>
using namespace  std;
//Возврат результата из потока по ссылке

void DoWork(int &a){ //имя функции это указатель на функцию !!!
    this_thread::sleep_for(chrono::milliseconds(2000));
    cout<<"id_потока: " <<this_thread::get_id()<<" ========\t"<< "DoWork STARTED\t========"<<endl;
    this_thread::sleep_for(chrono::milliseconds(5000));
       a*=2;
    cout<<"id_потока: " <<this_thread::get_id()<<" ========\t"<< "DoWork ENDED\t========"<<endl;
}

int main(){
    int q = 5;
    thread t(DoWork,std::ref(q)); //!!!  Используем std::ref(q)
    for (int i = 0; i<10; ++i) { //непрерывная работа
        cout<< "id_потока: " <<this_thread::get_id()<<"\tmain works\t"<<i<<endl;
        this_thread::sleep_for(chrono::milliseconds(500));
    }

    t.join();
    cout<<q<<endl;

    return 0;
}
