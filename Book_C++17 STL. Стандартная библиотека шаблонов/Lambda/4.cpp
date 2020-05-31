#include <iostream>
#include <string>

int main(){
	auto counter ([count = 0] () mutable { return ++count; } );
	for (size_t i {0}; i < 5; ++i) {
		std::cout << counter() << ", ";
	}
	std::cout << '\n';

	int a {0};  //значение переменной a увеличивается в замыкании и при этом доступно за его пределами
	auto incrementer ( [&a] { ++a; } );
	incrementer();
	incrementer();
	incrementer();
	std::cout << "Value of 'a' after 3 incrementer() calls: " << a << '\n';


}
