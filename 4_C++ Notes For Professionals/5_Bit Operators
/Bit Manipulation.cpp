
#include <iostream>
#include <iomanip>
#include <bitset>

int main(){
std::bitset<10> x;
x.set(); // Sets all bits to '1'
std::cout<<x<<std::endl;

  std::bitset<4> foo (std::string("1001"));
  std::bitset<4> bar (std::string("0011"));

  std::cout << (foo^=bar) << '\n';       // 1010 (XOR,assign)
  std::cout << (foo&=bar) << '\n';       // 0010 (AND,assign)
  std::cout << (foo|=bar) << '\n';       // 0011 (OR,assign)

  std::cout << (foo<<=2) << '\n';        // 1100 (SHL,assign)
  std::cout << (foo>>=1) << '\n';        // 0110 (SHR,assign)

  std::cout << (~bar) << '\n';           // 1100 (NOT)
  std::cout << (bar<<1) << '\n';         // 0110 (SHL)
  std::cout << (bar>>1) << '\n';         // 0001 (SHR)

  std::cout << (foo==bar) << '\n';       // false (0110==0011)
  std::cout << (foo!=bar) << '\n';       // true  (0110!=0011)

  std::cout << (foo&bar) << '\n';        // 0010
  std::cout << (foo|bar) << '\n';        // 0111
  std::cout << (foo^bar) << '\n';        // 0101

std::bitset<4> num(std::string("0100"));
num.flip(2); // num is now 0000
num.flip(0); // num is now 0001
num.flip(); // num is now 1110 (flips all bits)

std::bitset<4> num1(std::string("0010"));
bool bit_val = num1.test(1); // bit_val value is set to true;

std::bitset<5> num2(std::string("01100"));
num2.set(0);      // num is now 01101
num2.set(2);      // num is still 01101
num2.set(4,true); // num is now 11110

std::bitset<5> num3(std::string("01100"));
num3.reset(2);     // num is now 01000
num3.reset(0);     // num is still 01000
num3.set(3,false); // num is now 00000

std::bitset<5> num4(std::string("00100"));
num4.set(0,true); // num is now 00101
num4.set(2,false); // num is now 00001


char op1 = 'b'; // "a" letter (i.e. small case)
int mask = 0xDF; // choosing a proper mask
printf("a (AND) mask = A\n");
printf("%c  &  0xDF = %c\n", op1, op1 & mask);



}