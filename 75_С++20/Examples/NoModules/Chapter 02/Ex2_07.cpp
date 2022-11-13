// Finding maximum and minimum values for data types
#include <iostream>
#include <limits>
#include <format.h>

int main()
{
  std::cout
    << fmt::format("The range for type short is from {} to {}\n",
      std::numeric_limits<short>::min(), std::numeric_limits<short>::max())
    << fmt::format("The range for type unsigned int is from {} to {}\n",
      std::numeric_limits<unsigned int>::min(),
      std::numeric_limits<unsigned int>::max())
    << fmt::format("The range for type long is from {} to {}\n",
      std::numeric_limits<long>::min(), std::numeric_limits<long>::max())
    << fmt::format("The positive range for type float is from {} to {}\n",
      std::numeric_limits<float>::min(), std::numeric_limits<float>::max())
    << fmt::format("The full range for type float is from {} to {}\n",
      std::numeric_limits<float>::lowest(), std::numeric_limits<float>::max())
    << fmt::format("The positive range for type double is from {} to {}\n",
      std::numeric_limits<double>::min(),
      std::numeric_limits<double>::max())
    << fmt::format("The positive range for type long double is from {} to {}\n",
      std::numeric_limits<long double>::min(),
      std::numeric_limits<long double>::max());
}
