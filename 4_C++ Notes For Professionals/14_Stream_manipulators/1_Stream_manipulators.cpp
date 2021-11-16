#include <sstream>
#include <iostream>
#include <iomanip>
#include <locale>

using namespace std;

int main()
{
//std::boolalpha and std::noboolalpha - switch between textual and numeric representation of booleans.
std::cout << std::boolalpha << 1 <<"\n";
// Output: true
std::cout << std::noboolalpha << false <<"\n";
// Output: 0

bool boolValue;
std::cin >> std::boolalpha >> boolValue;
std::cout << "Value \"" << std::boolalpha << boolValue
<< "\" was parsed as " << std::noboolalpha << boolValue << "\n\n";
// Input: true
// Output: Value "true" was parsed as 1

//std::showbase and std::noshowbase - control whether prefix indicating numeric base is used.
//std::dec (decimal), std::hex (hexadecimal) and std::oct (octal) - are used for changing base for integers.

std::cout << std::dec << 29 << " - "
          << std::hex << 29 << " - "
          << std::showbase << std::oct << 29 << " - "
          << std::noshowbase << 29 << " - "
          << std::showbase << std::hex << 29
          << "\n\n";
// Output: 29 - 1d - 035 - 35

int number;
std::istringstream("3B") >> std::hex >> number;
std::cout << std::dec << number << "\n";
// 59
//Default values are std::ios_base::noshowbase and std::ios_base::dec .

std::cout << std::hex << std::showbase
<< "0x2a with nouppercase: " << std::nouppercase << 0x2a << '\n'
<< "1e-10 with uppercase: " << std::uppercase << 1e-10 << '\n';

//std::setw(n) - changes the width of the next input/output field to exactly n .

std::cout << "no setw:" << 51 << '\n'
          << "setw(7): " << std::setw(7) << 51 << '\n'
          << "setw(7), more output: " << 13
          << std::setw(7) << std::setfill('*') << 67 << ' ' << 94 << "\n\n";

std::cout.imbue(std::locale("en_US.utf8"));
std::cout << std::left << std::showbase << std::setfill('*')
<< "flt: " << std::setw(15) << -9.87 << '\n'
<< "hex: " << std::setw(15) << 41 << '\n'
<< " $: " << std::setw(15) << std::put_money(367, false) << '\n'
<< "usd: " << std::setw(15) << std::put_money(367, true) << '\n'
<< "usd: " << std::setw(15)
<< std::setfill(' ') << std::put_money(367, false) << "\n\n";

std::cout << std::right << std::showbase << std::setfill('*')
<< "flt: " << std::setw(15) << -9.87 << '\n'
<< "hex: " << std::setw(15) << 41 << '\n'
<< " $: " << std::setw(15) << std::put_money(367, false) << '\n'
<< "usd: " << std::setw(15) << std::put_money(367, true) << '\n'
<< "usd: " << std::setw(15)
<< std::setfill(' ') << std::put_money(367, true) << "\n\n";

//Остальное = см книгу

}
