#include <iostream>
#include <string>

int main() { //До С++ 11
	struct name_greeter {
		std::string name;
		void operator()() {
			std::cout << "Hello, " << name << '\n';
		}
	};
	name_greeter greet_john_doe {"John Doe"};
	greet_john_doe();
}
