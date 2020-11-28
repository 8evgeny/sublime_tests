#include <iostream>

enum Alphabet {
    a, b, c
};

enum class Digit : int {
    one, two, three
};

void accept_int(int) {
}

void accept_class_enum(Digit) {
}

void accept_enum(Alphabet) {
}

int main(int, char *[]) {
    accept_int(0);
    // accept_class_enum(0); // no known conversion from 'int' to 'Digit'
    // accept_enum(0); // no known conversion from 'int' to 'Alphabet'

    accept_int(a);
//    accept_class_enum(b); // no known conversion from 'Alphabet' to 'Digit'
    accept_enum(c);

//    accept_int(Digit::one); // no known conversion from 'Digit' to 'int'
    accept_class_enum(Digit::two);
//    accept_enum(Digit::three); // no known conversion from 'Digit' to 'Alphabet'

    return 0;
}
