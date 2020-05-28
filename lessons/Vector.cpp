#include <vector>
#include <cstdlib>
#include <iostream>
 
 
int main( )
{
    std::vector<int> c{5, 7, 8, 3, 4, 5, 6, 7, 8, 9};
    for (auto &i : c) { // !!!! Синтаксис !!!!
        std::cout << i << " ";
    }
    std::cout << '\n';
 
    c.erase(c.begin()); // Удаляем первый
 
    for (auto &i : c) {
        std::cout << i << " ";
    }
    std::cout << '\n';
 
    c.erase(c.begin()+2, c.begin()+5); //Удаляем со 2 по 5
 
    for (auto &i : c) {
        std::cout << i << " ";
    }
    std::cout << '\n';
 system( "PAUSE" ) ; return 0 ;    
}