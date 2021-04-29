#include <cstddef>
#include <iostream>

int main() {
  std::byte b{42};
  std::cout << std::to_integer<int>(b) << "\n";

  // b *= 2 compilation error
  b <<= 1;
  std::cout << std::to_integer<int>(b) << "\n";
  b <<= 1;
  std::cout << std::to_integer<int>(b) << "\n";
}
