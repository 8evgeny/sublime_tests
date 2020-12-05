#include "stdafx.h"
#include <iostream>

// using namespace NamespaceA;

namespace NamespaceA {
	namespace NamespaceB {
		namespace NamespaceC {
			struct MyStruct { };
		}
	}
}

using namespace NamespaceA;

int main()
{
	using namespace NamespaceA;
	using Add = NamespaceA::NamespaceB::NamespaceC::MyStruct;
	return 0;
}

