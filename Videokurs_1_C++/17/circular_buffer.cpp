// Circular Buffer

// видеорегистратор
// логи последних событий
// ролик в PS4
// китайские флэшки

#include <iostream>

#include <boost/circular_buffer.hpp>

// 0, 1, 2, 3, *
// B           E

// push_back(4)
// 4, 1, 2, 3
//    EB

// result for loop
// 4, 1, 2, 3
//    E     B

int main() {
    boost::circular_buffer<int> buffer{4};

    for (int i = 0; i < 10; ++i) {
        buffer.push_back(i);
    }

    for (int i : buffer) {
        std::cout << i << " ";
    }

    return 0;
}
