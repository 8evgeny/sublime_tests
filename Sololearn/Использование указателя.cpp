//#include <conio.h>
#include <iostream>
#include <cstdlib>
using namespace std;

class MyClass   //Создаем свой класс - только public
{
    public:
        MyClass();    
        void myPrint();
};

MyClass::MyClass() {         //Конструктор класса
}
void MyClass::myPrint() {  // Объявляем и описываем функцию
    cout <<"Hello"<<endl;
}

int main() {
    MyClass obj;            // Объект класса
    MyClass *ptr = &obj;    // Указатель на объект
    ptr->myPrint();         // Вызов функции через указатель

 //getch(); // Ожидаем символ
system("PAUSE");
 return 0;   
}  
