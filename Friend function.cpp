#include <conio.h>
#include <iostream>
#include <cstdlib>
using namespace std;


class MyClass {
    public:
        MyClass() {
            regVar = 0;
        }
    private:
        int regVar;
     //void someFunc(MyClass &obj);
    friend void someFunc(MyClass &obj);
};

void someFunc(MyClass &obj) {
    obj.regVar = 42;
    cout << obj.regVar;
}

int main() {
    MyClass obj;
    someFunc(obj);

 getch(); // Ожидаем символ

 return 0;   
}  
