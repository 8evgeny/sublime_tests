#include <iostream>
#include <mutex>
#include <string>
#include <thread>

using namespace std;

mutex m;

void foo()
{
    lock_guard< mutex > guard( m );
    cout << "Hello World!" << endl;
}

void foo2()
{
    lock_guard< mutex > guard( m );
    cout << "Hello2 World!2" << endl;
}

int main()
{
    thread t1( foo );
    thread t2( foo2 );

    t1.join();
    t2.join();

    return 0;
}
