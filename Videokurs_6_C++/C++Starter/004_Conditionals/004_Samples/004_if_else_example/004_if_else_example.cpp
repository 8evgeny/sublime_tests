#include "stdafx.h"
#include <iostream>
#include <string>   // модуль <string> предназначен для работы со строками

using namespace std;

int main()
{
    setlocale(LC_ALL, "rus");

	string name = "Vladimir";
	string password = "P@ss123";

	string userName;
    string userPass;

    // вводим имя пользователя
	cout << "Введите имя: ";
	cin >> userName;            
    
    if (userName == name)
    {
        // Если имя введенно верно, просим пользователя ввести пароль
        cout << "Введите пароль: ";
        cin >> userPass;

        if (userPass == password)
        {
            cout << "Здравствуйте " << userName << ". Вы вошли в систему!" << endl;
        }
        else
        {
            cout << "Неверный пароль!" << endl;
        }
    }
    else
    {
        cout << "Неверное имя пользователя!" << endl;
    }

	cin.get();
    return 0;
}

