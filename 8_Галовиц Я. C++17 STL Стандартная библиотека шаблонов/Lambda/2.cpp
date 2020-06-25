#include <iostream>

int main() {
	auto greet_john_doe ([] {std::cout << "Hello, John Doe\n";});
	greet_john_doe();
}