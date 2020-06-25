#include <conio.h>
#include <iostream>
#include <cstdlib>
using namespace std;

class MyClass
{
    public:
        void myPrint() const;
};

void MyClass::myPrint() const {    // Конструктор
    cout <<"Hello"<<endl;
}

int main() {
    const MyClass obj;
    obj.myPrint();

 getch(); // Ожидаем символ

 return 0;   
}  
