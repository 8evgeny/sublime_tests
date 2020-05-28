
#include <iostream>
#include <list>
#include <vector>
using namespace std;
        // List - двусвязный список  быстрое добавление и удаление элементов
        // оператор [] не реализован - только итераторы

template<class T>
void Printlist (const list<T> &lst)
{
    for (auto i = lst.cbegin(); i !=lst.cend(); ++i) // !! Итерация префиксная
    {
     cout<<*i<<endl;
     }
}

int main()
{

   // list<int> myList;
    list<int> myList = {17,19,176,-96};
     myList.push_back(5);
     myList.push_front(115);
    //list<int>::iterator it = myList.begin();
    // либо короче -
    auto it = myList.begin();
    cout<<*it<<endl<<endl;

for (auto i=myList.begin(); i !=myList.end(); i++) // Итерация постфиксная
{
 cout<<*i<<endl;
 }
cout<<endl;
Printlist(myList); // Функция Printlist заменяет цикл

// Метод sort()
cout<<endl;
myList.sort();
Printlist(myList);

// методы pop_back  и  pop_front  удаляют  последний и первый

cout<<endl;
myList.pop_back();
myList.pop_front();
Printlist(myList);

cout<<endl<<myList.size()<<endl; // колл. элементов

myList = {99,17,19,99,99,176,99,-96,99,99,99}; //Занесем новые значения
cout<<endl;
Printlist(myList);

myList.unique(); // Удалит последовательно идущие дубликаты
cout<<endl;
Printlist(myList);

myList.reverse(); //Реверс
cout<<endl;
Printlist(myList);

myList.clear(); //Очистка
cout<<endl;
Printlist(myList); // Ничего не выводит - там пусто
myList.push_back(5);
Printlist(myList);


list<int> myList1 = {17,19,176,2,45,-96};
auto it1 = myList1.begin();
cout<<endl;

cout<<"it1  - "<<it1.operator->()<<" "<<it1.operator*()<<endl; // !!!!! Куда указывает - 17


cout<<endl;
Printlist(myList1);

//Доступ к произвольному элементу через метод advice

advance(it1,2); //сдвигает  на 2 позиции - тут в цикле

cout<<endl;
cout<<it1.operator->()<<" "<<it1.operator*(); // 176

myList1.insert(it1,666);  // 666 вставляется на место 176 остальное сдвигается
cout<<endl;
Printlist(myList1);
cout<<endl;
cout<<it1.operator->()<<" "<<it1.operator*(); // Итератор указывает на 176

myList1.erase(it1); //удаляем 176
cout<<endl;
Printlist(myList1);

cout<<endl;
cout<<it1.operator->()<<" "<<it1.operator*(); // Итератор указывает на удаленный 176

 it++;
 cout<<endl;
 cout<<it1.operator->()<<" "<<it1.operator*(); // Итератор потерян !!!!!!!!!

 auto it2= myList1.begin();
 cout<<endl;
 cout<<it2.operator->()<<" "<<it2.operator*(); //Новый итератор - начало списка

 myList1.push_back(666);
 cout<<endl;
 Printlist(myList1);

myList1.remove(666); //Удаляет конкретное значение
cout<<endl;
Printlist(myList1);

myList.assign(4,666); //удаляет все и заполняем элементами
cout<<endl;
Printlist(myList);

myList.assign(myList1.begin(),myList1.end()); //Заполняем List значениями из List1
cout<<endl;
Printlist(myList);

return 0 ;
}
