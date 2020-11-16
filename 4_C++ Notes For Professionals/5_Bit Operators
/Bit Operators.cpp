
#include <iostream>
#include <iomanip>

void doXORSwap(int& a, int& b)
{
// Need to add a check to make sure you are not swapping the same
// variable with itself. Otherwise it will zero the value.
if (&a != &b)
{
// XOR swap
a ^= b;
b ^= a;
a ^= b;
}
}


int main(){
int a = 5;     // 0101b  (0x05)
int b = 12;    // 1100b  (0x0C)
int c = a | b; // 1101b  (0x0D)
std::cout << "a = " << a << ", b = " << b << ", c = " << c << std::endl;

a = 5;     // 0101b  (0x05)
b = 9;     // 1001b  (0x09)
c = a ^ b; // 1100b  (0x0C)
std::cout << "a = " << a << ", b = " << b << ", c = " << c << std::endl;

a=5;
b=8;
std::cout<<"a = " << a << ", b = " << b<< std::endl;
doXORSwap(a,b);
std::cout<<"a = " << a << ", b = " << b<< std::endl;

a = 6;     // 0110b  (0x06)
b = 10;    // 1010b  (0x0A)
c = a & b; // 0010b  (0x02)
std::cout << "a = " << a << ", b = " << b << ", c = " << c << std::endl;

a = 1;      // 0001b
b = a << 1; // 0010b
c = a << 10;// 010000000000b
std::cout << "a = " << a << ", b = " << b << ", c = " << c << std::endl;

a = 2;      // 0010b
b = a >> 1; // 0001b
std::cout << "a = " << a << ", b = " << b << std::endl;



}