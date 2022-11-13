// The width, alignment, fill, and 0 formatting options of std::format() 
#include <iostream>
#include <format.h>

int main()
{
  // Default alignment: right for numbers, left otherwise
  std::cout << fmt::format("{:7}|{:7}|{:7}|{:7}|{:7}\n", 1, -.2, "str", 'c', true);
  // Left and right alignment + custom fill character
  std::cout << fmt::format("{:*<7}|{:*<7}|{:*>7}|{:*>7}|{:*>7}\n", 1, -.2, "str", 'c', true);
  // Centered alignment + 0 formatting option for numbers
  std::cout << fmt::format("{:^07}|{:^07}|{:^7}|{:^7}|{:^7}\n", 1, -.2, "str", 'c', true);
}
