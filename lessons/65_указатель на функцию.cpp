#include <iostream>
#include <string.h>
using namespace std;


//СИНТАКСИС
// тип функции (*имя указателя)(спецификация параметров);

void foo1 (){
cout<<"void foo 1()"<<"\n";
};

void foo2 (){
cout<<"void foo 2()"<<"\n";
};

int foo3 (int a){
return a-1;
};

int foo4 (int a){
return a*2;
};

string GetDataFromBD(){
return "Data from BD";
};

string GetDataFromWebSerwer(){
return "Data from WebSerwer";
};

void ShowInfo(string (*foo)()){  // !!! в качестве параметра передаем указатель на функцию
cout<<foo()<<endl;

};




int main()
{

void (*foPointer)(); // Создали указатель в который можем записать адрес функции
//которая не возвращает накаких значений и не принимает никаких параметров !!!!!

foPointer = foo1; //Присвоили адрес функции foo1
foPointer(); // вызвали функцию

foPointer = foo2; //Присвоили адрес функции foo1
foPointer(); // вызвали функцию

int (*foPointer2)(int a);
//foPointer2 = foo1; - компилятор не пропустит (разная семантика)
foPointer2 = foo3;
cout<<foPointer2(12)<<"\n";

foPointer2 = foo4;
cout<<foPointer2(12)<<"\n";

ShowInfo(GetDataFromBD);
ShowInfo(GetDataFromWebSerwer);

    return 0;
}
