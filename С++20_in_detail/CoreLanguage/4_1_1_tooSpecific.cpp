// tooSpecific.cpp

#include <iostream>

void needInt(int i){
    std::cout << "int: " << i << '\n';
}

template <typename T>
auto add(T first, T second){
return first + second;
}



int main(){
	
    std::cout << std::boolalpha << '\n';
	
    double d{1.234};                             // (1)
    std::cout << "double: " << d << '\n';
    needInt(d);                                  // (2)            
    
    std::cout << '\n';
    
    bool b{true};                                // (3)
    std::cout << "bool: " << b << '\n';
    needInt(b);                                  // (4)
	
    std::cout << '\n';

    std::cout << "add bool: " << add(true, false) << '\n';

}

