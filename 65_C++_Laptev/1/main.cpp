#include <iostream>

using namespace std;

int main()
{
    unsigned char nn = 40; // символьная переменная
    cout << nn << ' ' << int(nn) << endl;
    cout << nn << ' ' << (int)nn << endl;  //Допускается - стиль С

//вывод кодов специальных символов
    cout << int('\t') << endl; // табуляция
    cout << int('\n') << endl; // новая строка
    cout << int('\a') << endl; // звуковой сигнал
    cout << int('\b') << endl; // backspace


    return 0;

}
