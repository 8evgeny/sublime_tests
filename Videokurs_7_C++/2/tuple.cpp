#include <iostream>
#include <tuple>
#include <functional>

int foo(int, int, std::string &result)
{
    result = "surname";
    return 127;
}

std::string foo(int, int, int &err)
{
    err = 127;
    return "surname";
}

void foo(int, int, int &err, std::string &result)
{
    err = 127;
    result = "surname";
}

struct result {
    int err;
    std::string result;
};

auto foo(int, int)
{
    return result{127, std::string("surname")};
}

auto bar(int, int)
{
    return std::tuple<int, std::string>(127, "surname");
//    return std::make_tuple(127, std::string("surname"));
}

int main(int, char *[])
{
    std::cout << "* return struct" << std::endl;
    auto rf = foo(1, 2);
    std::cout << rf.err << std::endl;
    std::cout << rf.result << std::endl;

    std::cout << "* return tuple" << std::endl;
    auto rb = bar(1, 2);
    std::cout << std::get<0>(rb) << std::endl;
    std::cout << std::get<1>(rb) << std::endl;

    std::cout << "* return and unpack " << std::endl;
    std::string result;
    int err;
    std::tuple<int &, std::string &>(err, result) = bar(1, 2);
//    std::make_tuple(std::ref(err), std::ref(result)) = bar(1, 2);
    std::cout << err << std::endl;
    std::cout << result << std::endl;

    std::cout << "* return and unpack" << std::endl;
    std::tie(err, result) = bar(1, 2);
    std::cout << err << std::endl;
    std::cout << result << std::endl;

    return 0;
}
