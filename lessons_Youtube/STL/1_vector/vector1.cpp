
#include <iostream>
#include <vector>  // Подключаем
using namespace std;

void print(vector<int> &v){
    // for(unsigned int i=0 ; i<myVector.size() ; i++)
    for (auto &i : v)
{
        cout<<"vector's element "<<i<<": "<<v[i]<<endl;
    }
    cout<<endl;
}

int main()
{
vector <int> myVector = { 2, -5, -8, 44, 4 };  //Определяем тип данных - int и имя нашего вектора -
//myVector и инициализируем значениями

myVector.push_back(222);
myVector.push_back(44);
myVector.push_back(77);
myVector.push_back(12);
myVector.push_back(587);
myVector.push_back(8);
myVector.push_back(-56);
myVector.push_back(97);


cout<<"number elements in vector: "<<myVector.size()<<endl;
print(myVector);

myVector.pop_back(); // метод удаляет последний элемент

cout<<" pop_back() number elements in vector: "<<myVector.size()<<endl;
print(myVector);


myVector[0] = 1000; //Доступ к элементу
myVector[3] = 25000;

myVector.at(0) = 1000; //Безопасный доступ к элементу работает медленнее
myVector.at(3) = 25000;

print(myVector);

myVector.clear(); //очистка всех элементов
cout<<" clear()  number elements in vector: "<<myVector.size()<<endl;

//Разобраться с исключениями - синтаксис
// try
// {
// myVector.at(25) = 5;
// }

// catch (const std :: out_of_rage & ex) //Генерируем исключение
// {
// cout << ex.what() << endl;
//}
return 0 ;
 }
