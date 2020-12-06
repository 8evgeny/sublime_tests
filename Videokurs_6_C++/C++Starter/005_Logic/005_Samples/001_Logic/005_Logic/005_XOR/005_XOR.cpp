#include "stdafx.h"
#include <iostream>

using namespace std;
/*
		»сключающее »Ћ» Ц это логическа€ операци€, став€ща€ в соответствие каждым двум простым высказывани€м составное 
		высказывание, €вл€ющеес€ истинными тогда, когда оба операнда различаютс€.


					-------------------------
					|	a	|	b	| ----	|
					-------------------------
					| true	| true	| false	|
					-------------------------
					| true	| false	| true	|
					-------------------------
					| false	| true	| true	|
					-------------------------
					| false	| false	| false	|
					-------------------------
*/

int main()
{
	bool a = true;		// 1
	bool b = false;		// 0

	bool result = (a || b) && !(a && b);	// 1 - true	

	cout << boolalpha << result << endl;

	return 0;
}