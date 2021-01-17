//Листинг 2.20. Определение кодов символов
//Откорректировано
#include <cstdio>
#include <iostream>
using namespace std;
int main (){
        const int Esc = 27; // ASCII-код ESC
        unsigned char ch = 0;
        while (ch != Esc) {
            ch = getchar();
            std::cout << ch << '=' << int(ch) << std::endl;
        }
return 0;

}

