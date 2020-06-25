
#include <iostream>
#include <vector>  // Подключаем
using namespace std;



int main()
{
vector <int> myVector = { 2, -5, -8, 555456, 2, };  //Определяем тип данных - int
//и имя нашего вектора - myVector и инициализируем значениями int

myVector.push_back(2);  //Добавляем в конец
myVector.push_back(44);
myVector.push_back(77);
myVector.push_back(-334);
myVector.push_back(22);
myVector.push_back(177);
myVector.push_back(1534);

cout<<"number elements in vector: "<<myVector.size()<<endl;
cout<<"capacity  "<<myVector.capacity()<<endl; //Емкость (память выделяетя с запасом)

for(unsigned int i=0 ; i<myVector.size() ; i++)
{
cout<<"vector's element "<<i<<": "<<myVector[i]<<endl;
}

myVector.reserve(1000); // !!!!! Устанавливаем значение capasity - Резерв ячеек
cout<<"number elements in vector: "<<myVector.size()<<endl;
cout<<"capacity  "<<myVector.capacity()<<endl;
myVector.shrink_to_fit(); //Освобождаем неиспользуемую память
cout<<"capacity  "<<myVector.capacity()<<endl;

return 0 ;
 }
