#include <iostream>
#include <thread>
#include <chrono>
using namespace  std;
//Создание потоков

void DoWork(){ //имя функции это указатель на функцию !!!
    for (int i = 0; i < 10; ++i) {
        cout<< "id_текущего потока: " <<this_thread::get_id()<<"\tDoWork\t"<<i<<endl;
        this_thread::sleep_for(chrono::milliseconds(1000));
    }
}

int main(){

    thread t1(DoWork);
    thread t2(DoWork);

    for (int i = 0; i < 10; ++i) {
        cout<< "id_текущего потока: " <<this_thread::get_id()<<"\tmain\t"<<i<<endl;
    this_thread::sleep_for(chrono::milliseconds(500));
    }

    thread t3(DoWork);
    t3.detach(); //поток в свободное плавание - с завершением main завершится

    t1.join(); //важно !! при встрече join основная логика блокируется и ждет завершения потока t1
    t2.join();
    return 0;
}

