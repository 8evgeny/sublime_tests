
#include <string>
#include <conio.h>
#include <stdlib.h>
using namespace std;
#include <bitset>
#include <iostream>
#include <string>
int main ()
{
using namespace std;
// создание объекта класса bitset
bitset <4> fourBits; // 4 бита, инициализированных 0000
cout << "Initial contents of fourBits: " << fourBits << endl;
bitset <5> fiveBits (31); // 5 битов 10101
cout << "Initial contents of fiveBits: " << fiveBits << endl;
bitset <5> fiveBits1 (32); // 5 битов
cout << "Initial contents of fiveBits: " << fiveBits1 << endl;
//bitset <12> twelveBits (101010101010); // 12 битов
//cout << "Initial contents of fiveBits: " << twelveBits << endl;
bitset <8> eightbits (255); // 8 битов, инициализированных
// значением 255 типа long int
cout << "Initial contents of eightBits: " << eightbits << endl;
// создание экземпляра набора битов как копии другого
bitset <8> eightBitsCopy(eightbits);
cout << "Initial contents of eightBits: " << eightBitsCopy << endl;

getch();
return 0;
}
// operator<< Передает текстовое представление битовой последовательности в
// поток вывода
// Cout << fourBits;
// operator>> Передает строку в объект класса bitset
// "0101" >> fourBits;
// operators & Выполняет побитовую операцию AND
// bitset <4> result (fourBitsl & fourBits2);
// operator | Выполняет побитовую операцию OR
// bitwise <4> result (fourBitsl | fourBits2);
// operator ^ Выполняет побитовую операцию XOR
// bitwise <4> result (fourBitsl ^ fourBits2);
// operator ~ Выполняет побитовую операцию NOT
// bitwise <4> result (~fourBitsl);
// operator >>= Выполняет бинарный оператор сдвига вправо
// fourBits >>= (2); // Сдвиг на два бита вправо
// operator <<= Выполняет бинарный оператор сдвига влево
// fourBits <<= (2) ; // Сдвиг на два бита влево
// operator [N] Возвращает ссылку на бит номер N в последовательности
// fourBits [2] =0; // установить третий бит в 0
// bool bNum = fourBits [2]; // читать третий бит
