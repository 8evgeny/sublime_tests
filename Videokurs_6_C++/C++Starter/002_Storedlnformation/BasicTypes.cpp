// BasicTypes.cpp : Defines the entry point for the console application.
//

#include <iostream>

using namespace std;

int main() {
  //#pragma region ÷≈Ћџ≈ „»—Ћј

  //----------------- 16 bit -----------------
  // типу short соответствуют типы short int, signed short, signed short int
  // целое со знаком

  short a = -32768;
  short int b = +32767;

  // целое без знака

  unsigned short c = 0;
  unsigned short int d = 65535;

  //----------------- 32 bit -----------------
  // типу int соответствуют типы signed, signed int
  // целое со знаком

  int e = -2147483648;
  int f = +2147483647;

  // типу unsigned соответствуют типы unsigned int, unsigned, unsigned int
  // целое без знака

  unsigned g = 0;
  unsigned int h = 4294967295;

  //----------------- 64 bit -----------------
  // типу long long соответствуют типы long int, signed long, signed long int
  // целое со знаком

  long i = -9223372036854775808;
  long int j = +9223372036854775807;

  // целое без знака

  unsigned long k = 0;
  unsigned long int l = 18446744073709551615;

  //#pragma endregion

  //#pragma region ¬≈ў≈—“¬≈ЌЌџ≈ „»—Ћј

  //----------------- 32 bit -----------------

  float m = 1.8E-38f;
  float n = 3.4E+38f;

  //----------------- 64 bit -----------------

  double o = 2.2E-308;
  double p = 1.8E+307;

  //#pragma endregion

  //#pragma region Ћќ√»„≈— »… “»ѕ
  //----------------- 8 bit -----------------

  // логическая величина истина\ложь

  bool s = true;   // 0000 0001
  bool t = false;  // 0000 0000

  //#pragma endregion

  //#pragma region —»ћ¬ќЋ№Ќџ… “»ѕ
  //----------------- 16 bit -----------------

  char u = 'A';

  //#pragma endregion

  //#pragma region —“–ќ ќ¬џ… “»ѕ

  // строка в формате UNICODE

  string w = "Hello world!";

  //#pragma endregion

  return 0;
}
