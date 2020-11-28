#include <iostream>

// https://en.cppreference.com/w/cpp/language/attributes

[[noreturn]]
void stub2() {
    throw std::logic_error("not implemented yet");
}

[[deprecated ("use 'stub2' instead")]]
int stub() {
    return 42;
}

int delta2secs(int d, char m) {
    switch (m) {
        case 'w':
            d *= 7.0;
            [[fallthrough]];
        case 'd':
            d *= 24.0;
        case 'h':
            d *= 60.0;
        case 'm':
            d *= 60.0;
        case 's':
            break;
        default:
            d = -1;
    }
    return d;
}

[[nodiscard]]
int last_error_code() {
    return 2;
}

int main([[maybe_unused]] int argc, char **) {
    stub();
//    stub2();

    std::cout << delta2secs(1, 'w') << std::endl;

    last_error_code();

//    [[maybe_unused]]
    int value = 77;

    return 0;
}
