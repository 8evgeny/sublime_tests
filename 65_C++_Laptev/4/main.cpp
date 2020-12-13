#include <iostream>

using namespace std;

double Average(double data){
    static double summa = 0; // инициализация статических
    static int count =0 ;    // переменных при первом вызове
    count++;
    summa += data;
    return summa / count; // возврат нового среднего значения
}

int main()
{
double data = 1, middle;
while (data) // пока не задали ноль
{ cout << "Введите число: ";
cin >> data;
middle = Average(data); // вычисление очередного среднего
cout << "Среднее значение: " << middle << endl;
}
return 0;


    return 0;

}
