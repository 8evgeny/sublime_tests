#include "stdafx.h"
#include <iostream>
#include "nmsp.h"

namespace NamespaceA {
	void mul(int a, int b) {
		std::cout << (a * b) << std::endl;
	};
}

using namespace NamespaceA;

int main() {	

	mul(10, 42);

	return 0;
}