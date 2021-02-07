#include <iostream>
#include <thread>
#include <chrono>
using namespace  std;
//Передача параметров в поток

void DoWork(int a,int b,string msg){ //имя функции это указатель на функцию !!!
        cout<<msg<<endl;
        this_thread::sleep_for(chrono::milliseconds(2000));
        cout<<"========\t"<< "DoWork STARTED\t========"<<endl;
        this_thread::sleep_for(chrono::milliseconds(3000));
        cout<<"a+b= "<<a+b<<endl;
        cout<<"========\t"<< "DoWork ENDED\t========"<<endl;
        this_thread::sleep_for(chrono::milliseconds(1000));
}

int main(){

    thread th(DoWork,2,3,"ouwer message"); //!!! Передаем указатель на функцию и параметры

    for (int i = 0; true; ++i) { //непрерывная работа
        cout<< "id_потока: " <<this_thread::get_id()<<"\tmain works\t"<<i<<endl;
        this_thread::sleep_for(chrono::milliseconds(500));
    }


    th.join();
    return 0;
}

