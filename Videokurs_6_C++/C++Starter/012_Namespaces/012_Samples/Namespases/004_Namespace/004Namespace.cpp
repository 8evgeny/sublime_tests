#include "stdafx.h"
#include <iostream>
#include "nmsp.h"

namespace NamespaceA {
	void mul(int a, int b) {
		std::cout << (a * b) << std::endl;
	};
}

int main() {

	NamespaceA::mul(15, 42);

	return 0;
}