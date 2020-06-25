#include <conio.h>
#include <iostream>
#include <cstdlib>
using namespace std;

class MyClass
{
    public:
        MyClass();
        void myPrint();
};

MyClass::MyClass() {
}
void MyClass::myPrint() {
    cout <<"Hello"<<endl;
}

int main() {
    MyClass obj;
    obj.myPrint();

 getch(); // Ожидаем символ

 return 0;   
}  
