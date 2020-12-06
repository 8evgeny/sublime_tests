#include "stdafx.h"
#include <iostream>

namespace NamespaceA {
	namespace NamespaceB {
		namespace NamespaceC {
			struct MyStruct {

			};
		}
	}
}

int main()
{
	using _Struct = NamespaceA::NamespaceB::NamespaceC::MyStruct;
	
	_Struct variable1;

	return 0;
}



