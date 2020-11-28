#include <iostream>
#include <vector>

struct foo
{
    foo() = delete;
    virtual ~foo() = default;

    virtual void m() final {};
    virtual void n() {};
};

class bar final : foo
{
   // void m() override {}; // overrides a 'final'
    void n() override {};
//   void o() override {}; // only virtual member functions can be marked 'override'
};

// class baz : bar
// {
// }

int main(int, char *[]) {
    return 0;
}
