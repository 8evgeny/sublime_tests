#include <string>

void foo()
{
    static std::string hw{"Hello, World!"};
};

bool hw_guard; // = 0, = false
std::string hw;

void bar()
{
    if (!hw_guard) {
        hw = "Hello, World!";
        hw_guard = true;
    }
};

int main(int, char* [])
{
    foo();
    bar();
    return 0;
}
