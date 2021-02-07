#include <thread>
#include <mutex>
#include "SimpleTimer.h"
using namespace  std;
//mutex cинхронизация потоков

   mutex mtx;
void Print(char ch){
    this_thread::sleep_for(chrono::milliseconds(2000));//!! Этот код не синхронизируется мьютексом и выполняется параллельно
    mtx.lock();
    for (int i = 0; i < 5; ++i) {
        for (int i = 0; i < 10; i++) {

        cout<<ch;
        this_thread::sleep_for(chrono::milliseconds(20));
        }
        cout<<endl;
    }
    cout<<endl;
    mtx.unlock();
    this_thread::sleep_for(chrono::milliseconds(2000));//!! Этот код не синхронизируется мьютексом и выполняется параллельно
}



int main(){
    SimpleTimer timer;
    thread t1(Print,'*');
    thread t2(Print,'#');
    thread t3(Print,'@');
    t1.join();
    t2.join();
    t3.join();
    return 0;
}
