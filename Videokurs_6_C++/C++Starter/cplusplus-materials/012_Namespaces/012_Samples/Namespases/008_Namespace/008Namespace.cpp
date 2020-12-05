#include "stdafx.h"
#include <iostream>

namespace NamespaceA {
	namespace NamespaceB {
		namespace NamespaceC {
			struct MyStructC {

			};
		}
		struct MyStructB {

		};
	}

	struct MyStructA {
		
	};
}

int main()
{
	using A = NamespaceA::MyStructA;
	using B = NamespaceA::NamespaceB::MyStructB;
	using С = NamespaceA::NamespaceB::NamespaceC::MyStructC;

	return 0;
}



