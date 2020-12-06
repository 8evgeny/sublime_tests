#include "stdafx.h"
#include <iostream>

namespace NamespaceA {
	struct MyStructA {

	};
};

namespace NamespaceA {
	// Нельзя создавать типы с одинаковым именем в одноименных пространствах имен
	/*struct MyStructA {

	};*/
	struct MyStructB {

	};
};

int main()
{
	using namespace NamespaceA;

	MyStructA variable1;
	MyStructB variable2;

	return 0;
}


