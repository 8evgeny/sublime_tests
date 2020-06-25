#include <iostream>
#include <vector>  // Подключаем
using namespace std;

int main()
{
    int arr[] = { 2,6,9 };
    cout<<arr[1]<<endl;
    cout<< *(arr+1)<<endl; // Арифметика указателей

vector<int> myVector = { 5,9,44,422,676,78,-38,55,-345,2,5687,3 };
cout<<myVector[1]<<endl;
// У остальных контейнеров [] не перегружены
//У каждого типа контейнеров есть свой итератор
 vector<int>::iterator it; //Объявляем итератор
cout<<endl;
 it = myVector.begin();
cout<< *it <<endl;
*it = 1000; // Изменяем 1 элемент Вектора
cout<< *it <<endl;
cout<<endl;
it++;  //Получили доступ к следующему элементу
cout<< *it <<endl;
it+=2; //сдвинулись вправо на 2 элемента
cout<< *it <<endl;
it--; //сдвинулись влево на 1 элемент
cout<< *it <<endl;
cout<<endl;

//Пройдем в цикле по вектору

// метод  end  указывает в никуда - после последнего элемента
for (vector<int>::iterator iter=myVector.begin(); iter != myVector.end(); iter++ )// !!!!!!!!!
{
cout<< *iter <<endl;
}

return 0 ;

}

