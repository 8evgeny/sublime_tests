// BasicTypes.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>

using namespace std;

int main()
{
	#pragma region ЦЕЛЫЕ ЧИСЛА
    
	//----------------- 16 bit -----------------
	// Типу short соответствуют типы short int, signed short, signed short int 
	// Целое со знаком
	
	short		a = -32768;
	short int	b = +32767;
	
	// Целое без знака
	
	unsigned short		c = 0;
	unsigned short int	d = 65535;

	//----------------- 32 bit -----------------
	// Типу int соответствуют типы signed, signed int
	// Целое со знаком

	int		e = -2147483648;
	int		f = +2147483647;

	// Типу unsigned соответствуют типы unsigned int, unsigned, unsigned int
	// Целое без знака

	unsigned		g = 0;
	unsigned int	h = 4294967295;

	//----------------- 64 bit -----------------
	// Типу long long соответствуют типы long int, signed long, signed long int 
	// Целое со знаком

	long		i = -9223372036854775808;
	long int	j = +9223372036854775807;

	// Целое без знака
	
	unsigned long		k = 0;
	unsigned long int	l = 18446744073709551615;

	#pragma endregion

	#pragma region ВЕЩЕСТВЕННЫЕ ЧИСЛА

	//----------------- 32 bit ----------------- 

	float m = 1.8E-38f;
	float n = 3.4E+38f;

	//----------------- 64 bit -----------------

	double o = 2.2E-308;
	double p = 1.8E+307;	
	
	#pragma endregion

	#pragma region ЛОГИЧЕСКИЙ ТИП
	//----------------- 8 bit -----------------

	// Логическая величина Истина\Ложь

	bool s = true;   // 0000 0001
	bool t = false;  // 0000 0000
	
	#pragma endregion

	#pragma region СИМВОЛЬНЫЙ ТИП
	//----------------- 16 bit -----------------
	
	char u = 'A';

	#pragma endregion
	
	#pragma region СТРОКОВЫЙ ТИП

	// Строка в формате UNICODE

	string w = "Hello world!";

	#pragma endregion


    return 0;
}

