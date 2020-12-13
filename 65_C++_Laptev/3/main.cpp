#include <iostream>

using namespace std;

int main()
{
    unsigned int counter = 0;
    for ( double summa = 0.0,  number;                    // это не оператор
         (cout << "Введите число: ", cin >> number);      // это не оператор
         summa += number, ++counter)                      // пустое тело
          cout << "Среднее=" << summa / counter << endl;

    return 0;

}
