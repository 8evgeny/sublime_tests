#include "stdafx.h"
#include <iostream>

using namespace std;

int main()
{
    setlocale(LC_ALL, "rus");

    int number;
    cout << "Введите число 1 или 2: " << endl;
    cin >> number;

    // ­  На 16-й строке создаем оператор многозначного выбора, и в качестве выражения селектора передаем переменную - number
    
    switch (number)     // (number) - выражение селектор
    {
        case 1:         // 1-е Постоянное выражение
        {
            cout << "Один" << endl;     // Ветвь 1
            break;
        }
        case 2:         // 2-е Постоянное выражение
        {
            cout << "Два" << endl;      // Ветвь 2
            break;
        }
    }
    
    cin.get();
    return 0;
}

