#include "stdafx.h"
#include <iostream>

namespace NamespaceA {
	namespace NamespaceB {
		namespace NamespaceC {
			int add(int a, int b) {
				return a + b;
			}
		}
	}
}

int main()
{
	using namespace NamespaceA::NamespaceB::NamespaceC;

	int x = 6;
	int y = 19;

	int sum = add(x, y);

	std::cout << sum << std::endl;

	return 0;
}



