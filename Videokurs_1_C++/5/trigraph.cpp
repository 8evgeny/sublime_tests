#include <iostream>
#include <string.h>
// https://en.cppreference.com/w/cpp/language/operator_alternative

int main(int argc, char **argv) {
    int x = 0; // Почему не работает инкремент ??/
    ++x;
    std::cout << "x = " << x << std::endl;

    if (argc > 1 and strcmp(argv[1], "help") == 0)
    {
        std::cout << "Держитесь там!" << std::endl;
    }

    return 0;
}
