#include <iostream>
#include <vector>

int main(){
for(int i = 0; i < 10; i++) {
std::cout << i << std::endl;
}
std::cout << std::endl;

// A valid loop is also:
for(int a = 0, b = 10, c = 20; (a+b+c < 100); c--, b++, a+=c) {
std::cout << a << " " << b << " " << c << std::endl;
}
std::cout << std::endl;

// // infinite loop
// for (;;)
// std::cout << "Never ending!\n";
// // The while loop equivalent of the above is:
// // infinite loop
// while (true)
// std::cout << "Never ending!\n";

// The next common example of iterating over all elements from an STL collection (e.g., a vector) without using the
// <algorithm> header is:
std::vector<std::string> names = {"Albert Einstein", "Stephen Hawking", "Michael Ellis"};
for(std::vector<std::string>::iterator it = names.begin(); it != names.end(); ++it) {
std::cout << *it << std::endl;
}




}