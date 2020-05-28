#include <array>
#include <iostream>
using namespace std;



int main()
{

array<int,4> arr = {1,94,77,9};
array<int,4> arr2 = {1,94,77,9};
//Объявили 2 одинаковых массива

bool result = (arr==arr2); //скобки можно не ставить
cout<<result<<endl;

// Если поместить в контейнеры объекты класса
//то для реализации операторов они должны быть перегружены в этом классе !!!!






return 0 ;
 }
