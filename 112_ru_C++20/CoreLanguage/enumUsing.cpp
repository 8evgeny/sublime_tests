// enumUsing.cpp

#include <iostream>
#include <string_view>

enum class Color {
    red,
    green, 
    blue
};

std::string_view toString(Color col) {
  using enum Color;
  switch (col) {

    case red:   return "red";           
    case green: return "green";         
    case blue:  return "blue";          
  }
  return "unknown";
}

int main() {

    std::cout << '\n';
   
    std::cout << "toString(Color::red): " << toString(Color::red) << '\n';
    
    using enum Color;                                                    
    
    std::cout << "toString(green): " << toString(green) << '\n';     
    
    std::cout << '\n';

}
