// Formatting numeric values with std::format() 
#include <iostream>
#include <format.h>
#include <numbers>

int main()
{
  const double pi{ std::numbers::pi };
  std::cout << fmt::format("Default: {:.2}, fixed: {:.2f}, scientific: {:.2e}, "
    "general: {:.2g}\n", pi, pi, pi, pi);
  std::cout << fmt::format("Default: {}, binary: {:b}, hex.: {:x}\n", 314, 314, 314);
  std::cout << fmt::format("Default: {}, decimal: {:d}, hex.: {:x}\n", 'c', 'c', 'c');
  std::cout << fmt::format("Alternative hex.: {:#x}, binary: {:#b}, HEX.: {:#X}\n",
    314, 314, 314);
  std::cout << fmt::format("Forced sign: {:+}, space sign: {: }\n", 314, 314);
  std::cout << fmt::format("All together: {:*<+10.4f}, {:+#09x}\n", pi, 314);
}
