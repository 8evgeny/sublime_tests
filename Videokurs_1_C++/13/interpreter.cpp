// Интерпретатор (Interpreter)

// config
// serialize

#include <iostream>

std::string seq;

void state_text(char);

auto active_handler = &state_text;

void state_exec(char c) {
    std::cout << "обработана последовательность " << seq << std::endl;
    active_handler = &state_text;
    active_handler(c);
}

void state_seq(char c) {
    if (c == 'm') {
        active_handler = &state_exec;
    } else {
        seq += c;
    }
}

void state_esc(char) {
    std::cout << "обнаружен ESC" << std::endl;
    seq.clear();
    active_handler = &state_seq;
}

void state_text(char c) {
    if (c == '\x1b') {
        active_handler = &state_esc;
        active_handler(c);
    } else {
        std::cout << c << std::endl;
    }
}

int main(int, char *[]) {
    std::string hw = "\x1b[41mHello,\x1b[40;3;31m World\x1b[m!";
    std::cout << hw << std::endl;

    for (auto c: hw) {
        active_handler(c);
    }

    return 0;
}
