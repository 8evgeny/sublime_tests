#include "stdafx.h"
#include <iostream>

using namespace std;
/*
	Конъюнкция – это логическая операция, ставящая в соответствие каждым двум простым высказываниям составное высказывание, 
	являющееся истинным только тогда, когда оба исходных высказывания истинны. Операция конъюнкции по своему применению
	близка к союзу «И». 

					-------------------------
					|	a	|	b	|	&&	|
					-------------------------
					| true	| true	| true	|
					-------------------------
					| true	| false	| false	|
					-------------------------
					| false	| true	| false	|
					-------------------------
					| false	| false	| false	|
					-------------------------
*/

int main()
{
	bool a = true;		// 1
	bool b = true;		// 0

	bool result = a && b;

	cout << boolalpha << result << endl;

    return 0;
}

//#include "stdafx.h"
//#include <iostream>
//
//using namespace std;
//
//int main()
//{
//
//
//	return 0;
//}