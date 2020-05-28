#include <iostream>
#include <vector>
#include <algorithm>
#include <conio.h>
using namespace std;

// Если не глядя заменить в листинге  все слова vector  словом  deque , его код
// все еще будет компилироваться и прекрасно работать. Это демонстрация простоты работы
// итераторов с алгоритмами и контейнерами.


int main()
{
// Динамический массив целых чисел
vector <int> vecIntegerArray;
// Вставить примеры целых чисел в массив
vecIntegerArray.push_back(50);
vecIntegerArray.push_back(2991);
vecIntegerArray.push_back(44);
vecIntegerArray.push_back(336);
vecIntegerArray.push_back(3899);
vecIntegerArray.push_back(2);
vecIntegerArray.push_back(127892);
vecIntegerArray.push_back(23);
vecIntegerArray.push_back(9999);
cout << "Soderzimoe vectora: " << endl;

// Обход вектора и чтение значений с помощью итератора
vector <int>::iterator iArrayWalker = vecIntegerArray.begin() ; 
//Установили итератор на 1 элемент используя класс iterator 

// а это альтернативный вариант если поддерживает компилятор (совместим с C++11)
//auto iArrayWalker = vecIntegerArray.begin (); // тип обнаруживает компилятор

while(iArrayWalker != vecIntegerArray.end())
{
// Вывод значения на экран
cout << *iArrayWalker << endl;
// Инкремент итератора для доступа к следующему элементу
++iArrayWalker;
}
int element;
cout << "Chto isem ? " ;
cin >> element ;
// Поиск элемента (скажем, 2991) с помощью алгоритма 'find
vector <int>::iterator iElement = find(vecIntegerArray.begin(), vecIntegerArray.end(), element);
// Проверить, найдено ли значение
if (iElement != vecIntegerArray.end())
{
// Значение найдено. Определяем позицию в массиве:
int elPos = distance(vecIntegerArray.begin() , iElement);
cout << "Znachenie"<< *iElement;
cout << " nahoditsya v pozicii " << elPos << endl;
}
else {
cout << "Znachenie  ne naideno ";	
}


getch(); 
return 0;
}


