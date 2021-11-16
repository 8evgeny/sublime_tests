#include <sstream>
#include <string>
#include <iostream>

using namespace std;

class foo
{
// All sort of stuff here.
};

ostream &operator<<(ostream &os, const foo &f)
{
    return os << f; //my
}


int main()
{
ostringstream ss;
ss << "the answer to everything is " << 42;
const string result = ss.str();
std::cout << result << "\n";




foo f;
ostringstream ss1;
ss1 << f;
const string result1 = ss1.str();
std::cout << result1 << "\n";

}
