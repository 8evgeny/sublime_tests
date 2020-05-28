
#include <conio.h>
#include <iostream>
#include <cstdlib>
using namespace std;
#include <ctime>


int main () {
  srand(time(0));

  for (int x = 1; x <= 10; x++) {
    cout << 1 + rand()  << endl;
  }

getch(); // Ожидаем символ

 return 0;
}
