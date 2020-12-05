//Напишите программу, которая позволяет пользователю ввести в консоли латинскую букву нижнего регистра,
//переводит её в верхний регистр и результат выводит в консоль.

#include <iostream>
using namespace std;
int main()
{
    char s;
    cout<<"Введите букву нижнего регистра:"<<endl;
    cin>>s;
//    cout<<"s= "<<s<<endl;
//    auto ps = &s;
//    cout<<"*ps= "<<*ps<<endl;
    auto ss = toupper(s);
    cout<<"Код: "<<ss<<endl;
    cout<<"\nТа же буква в верхнем регистре: ";
    putchar(ss);
    cout<<endl;
    s=s-32;
    cout << "\nТа же буква в верхнем регистре: " << s << ".\n\n";
    return 0;
}
