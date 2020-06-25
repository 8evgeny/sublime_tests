#include <iostream>
#include <string>

int main(){
	auto just_one ( []() { return 1; } );
	auto just_two ( [] { return 2; } );
	std::cout << just_one() << ", " << just_two() << '\n';
	auto plus ( [](auto l, auto r) { return l + r; } );
	std::cout << plus(1, 2) << '\n';
	std::cout << plus(std::string{"a"}, "b") << '\n';
	std::cout << plus(std::string("c"), std::string("d")) << '\n';
	std::cout << [](auto l, auto r) { return l + r; }(4, 8)  << '\n';
	std::cout << [](auto l, auto r) { return l + r; }(std::string("4"), std::string("8"))  << '\n';
}
