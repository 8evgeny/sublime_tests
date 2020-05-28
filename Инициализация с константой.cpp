#include <conio.h>
#include <iostream>
#include <cstdlib>
using namespace std;

class MyClass {
    public:
        MyClass(int a, int b);
    int regVar;
    const int constVar;
    
    private:
        
};

MyClass::MyClass(int a, int b)
: regVar(a), constVar(b)
{
    cout << regVar << endl;
    cout << constVar << endl;
}

int main() {

    MyClass obj(42, 33);
obj.regVar = 44;
//obj.constVar = 55;

	//cout << regVar << endl;
    //cout << constVar << endl;

 getch(); // Ожидаем символ

 return 0;   
}  
