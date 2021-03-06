#include <iostream>
#include <string>

// *************************************

void printAll() {
    std::cout << std::endl;
}

template<typename T, typename... Args>
void printAll(T first, Args... args) {
    std::cout << first << ' ';
    printAll(args...);
}


// *************************************

template<typename T>
T sumAll(T last) {
    return last;
}

template<typename T, typename... Args>
auto sumAll(T first, Args... args) {
    return first + sumAll(args...);
}

// *************************************

template<typename... Args>
void sumAll_2_fake_function(Args&&... ) {

}

template<typename T, typename... Args>
auto sumAll_2(T first, Args... args) {
    T sum = first;
    sumAll_2_fake_function((sum += args)...);
    return sum;
}

// *************************************

template<typename... Args>
auto rightUnaryFold(Args... args) {
    // + - * / % ^ & | = < > << >> += -= *=
    // /= %= ^= &= |= <<= >>= == != <= >= && || , .* ->*
    return (args + ...); // arg1 + (arg2 + (arg3 + (...)))
}

template<typename... Args>
auto leftUnaryFold(Args... args) {
    return (... + args); // ((arg1 + arg2) + arg3) + ...
}

struct SumLog {
    int value;

    SumLog(int v) : value{v} {};

    SumLog operator+(const SumLog& other) {
        std::cout << "operator+ with this = " << value;
        std::cout << " and other = " << other.value << std::endl;
        SumLog tmp{*this};
        tmp.value += other.value;
        return tmp;
    }

    SumLog& operator+=(const SumLog& other) {
        std::cout << "operator+ with this = " << value;
        std::cout << " and other = " << other.value << std::endl;
        value += other.value;
        return *this;
    }
};

std::ostream& operator<<(std::ostream& stream, const SumLog& value) {
    stream << value.value;
    return stream;
}

// ***************************************

    // + - * / % ^ & | = < > << >> += -= *=
    // /= %= ^= &= |= <<= >>= == != <= >= && || , .* ->*
template<typename... Args>
void binaryFold(Args... args) {
    (std::cout << ... << args) << std::endl;
}

template<typename... Args>
void binaryFold2(Args... args) {
    std::string result;
    (result += ... += std::to_string(args));
    std::cout << result << std::endl;
}

template<typename T, typename... Args>
auto binaryFoldLeft(T sum, Args... args) {
    (sum += ... += args);
    return sum;
}

template<typename T, typename... Args>
auto binaryFoldRight(T sum, Args... args) {
    (args += ... += sum);
    return sum;
}

int main() {
    printAll(1, "2", std::string("3"), std::to_string(4), 5.0, 6.0f, 7, 8, 9, 10);
    std::cout << std::endl;

    std::cout << "sumAll = " << sumAll(1, 2, 3, 4, 5, 6, 7, 8, 9, 10) << std::endl;
    std::cout << "sumAll = " << sumAll(1, 2.0, 3.0f, 4, 5, 6, 7, 8, 9, 10) << std::endl;
    std::cout << "sumAll = " 
            << sumAll(std::to_string(1), std::to_string(2), std::to_string(3)) 
            << std::endl << std::endl;
//     std::cout << "sumAll = " << sumAll("1", "2", "3", "4", "5") << std::endl;


    std::cout << "sumAll_2 = " << sumAll_2(1, 2, 3, 4, 5, 6, 7, 8, 9, 10) << std::endl;
    std::cout << "sumAll_2 = " << sumAll_2(1, 2.0, 3.0f, 4, 5, 6, 7, 8, 9, 10) << std::endl;
    std::cout << "sumAll_2 = " 
            << sumAll_2(std::to_string(1), std::to_string(2), std::to_string(3)) 
            << std::endl << std::endl;

    std::cout << "===" << std::endl;
    std::cout << "rightUnaryFold = " << rightUnaryFold(1, 2, 3, 4, 5, 6, 7, 8, 9, 10) << std::endl;
    std::cout << "rightUnaryFold = " 
            << rightUnaryFold(std::to_string(1), std::to_string(2), std::to_string(3)) 
            << std::endl << std::endl;
    // std::cout << "rightUnaryFold = " << unaryFold("1", "2", "3", "4", "5") << std::endl;

    std::cout << "leftUnaryFold = " << leftUnaryFold(1, 2, 3, 4, 5, 6, 7, 8, 9, 10) << std::endl;
    std::cout << "leftUnaryFold = " 
            << leftUnaryFold(std::to_string(1), std::to_string(2), std::to_string(3)) 
            << std::endl << std::endl;
    // std::cout << "leftUnaryFold = " << unaryFold("1", "2", "3", "4", "5") << std::endl;

    std::cout << "rightUnaryFold = \n"
        << rightUnaryFold(SumLog{1}, SumLog{2}, SumLog{3}, SumLog{4}, SumLog{5})
        << std::endl << std::endl;
    // (1 + (2 + (3 + (4 + 5))))

    std::cout << "leftUnaryFold = \n"
        << leftUnaryFold(SumLog{1}, SumLog{2}, SumLog{3}, SumLog{4}, SumLog{5})
        << std::endl << std::endl;
    // ((((1 + 2) + 3) + 4) +  5);

    std::cout << "binaryFold = ";
    binaryFold(1, "2", std::string("3"), std::to_string(4), 5.0, 6.0f, 7, 8, 9, 10);
    std::cout << std::endl;

    std::cout << "binaryFold2 = ";
    binaryFold2(1, 2, 3, 4, 5, 6, 7, 8, 9, 10);
    std::cout << std::endl;

    std::cout << "binaryFoldLeft:" << std::endl;
    std::cout << binaryFoldLeft(SumLog{1}, SumLog{2}, SumLog{3}, SumLog{4}, SumLog{5});
    std::cout << std::endl << std::endl;
    // ((((sum += 2) += 3) += 4) += 5);

    std::cout << "binaryFoldRight:" << std::endl;
    std::cout << binaryFoldRight(SumLog{1}, SumLog{2}, SumLog{3}, SumLog{4}, SumLog{5});
    std::cout << std::endl << std::endl;
    // (2 += (3 += (4 += (5 += sum))))

    return 0;
}
