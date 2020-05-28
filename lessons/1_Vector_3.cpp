
#include <iostream>
#include <vector>  
#include <random>
#include <ctime>
#include <algorithm>
using namespace std;

int main()
{
vector <int> myVector (4); //Явное указание колл элементов
cout<<"number elements in vector: "<<myVector.size()<<endl;
cout<<"capacity  "<<myVector.capacity()<<endl; //Емкость (память выделяетя с запасом)
for(unsigned int i=0 ; i<myVector.size() ; i++)
{
cout<<"vector's element "<<i<<": "<<myVector[i]<<endl;
}
cout<<myVector.empty()<<endl; //Возвращает 1 если вектор пуст
vector <int> myVec (5, -55); //Явное указание колл и инициализация значением
cout<<"number elements in vector: "<<myVec.size()<<endl;
cout<<"capacity  "<<myVec.capacity()<<endl; //Емкость (память выделяетя с запасом)
for(unsigned int i=0 ; i<myVec.size() ; i++)
{
cout<<"vector's element "<<i<<": "<<myVec[i]<<endl;
}
cout<<myVec.empty()<<endl; //Возвращает 1 если вектор пуст

vector <int> myVec2;
cout<<myVec2.empty()<<endl; //Возвращает 1 если вектор пуст

cout<<"number elements in vector: "<<myVec2.size()<<endl;
cout<<"capacity  "<<myVec2.capacity()<<endl;

myVec2.resize(20,448);  //Метод изменяет размер вектора
// и можно его сразу инициализировать 448
cout<<"number elements in vector: "<<myVec2.size()<<endl;
cout<<"capacity  "<<myVec2.capacity()<<endl;

// заполним рандомными числами
std::mt19937 gen(static_cast<unsigned int>(time(nullptr)));
std::uniform_int_distribution<> randomDigit(1, 20);
vector <int>  v ;
int size = randomDigit(gen);
	for (int i=0; i<size; ++i) 
	{
		v.push_back(randomDigit(gen));
		cout <<v[i]<<"\t";
	}
	cout << endl;
	// Сортируем
	sort (v.begin(), v.end());
	for (int i = 0; i<size; ++i)
	{
		cout << v[i] << "\t" ;
	}
	cout << endl;
	//Реверс
	reverse(v.begin(), v.end());
	for (int i = 0; i<size; ++i)
		{
		cout <<v[i]  << "\t" ;
		}
	cout << endl;

// system("pause");
return 0 ;
 }
