#include "stdafx.h"
#include <iostream>
#include <string>

using namespace std;

int main()
{
	string login = "Admin";
	string password = "12345";

	string userLogin = "";
	string userPassword = "";

	cout << "Enter your login: ";	
	cin >> userLogin;

	cout << "Enter the password: ";
	cin >> userPassword;

	if (userLogin == login && userPassword == password) {
		cout << "Hello, Admin!" << endl;
	}
	else
	{
		cout << "Hello, User!" << endl;
	}

	system("pause");
	return 0;
}