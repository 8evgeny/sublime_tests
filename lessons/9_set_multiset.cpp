
#include <iostream>
#include <set> // Подключаем
using namespace std;

template<class T>
void print(const set<T> &name){
for (auto &item:name){
 cout<<" "<<item<<" ";
}
cout<<endl<<endl;
};

template<class T>
void print2(const multiset<T> &name){
for (auto &item:name){
 cout<<" "<<item<<" ";
}
cout<<endl<<endl;
};






int main()
{
// Реализованы на основе бинарного дерева

set<int> mySet;
// Для добавления используется метод  insert

mySet.insert(5);
mySet.insert(1);
mySet.insert(12);
mySet.insert(4);
mySet.insert(-12);

print(mySet);

 // Set  поддерживает список инициализации

mySet.clear(); //- очистка

mySet = {1,44,6,13,666,-34,-2,43}; //очистку перед присвоением можно и не делать
mySet.insert(44); //44 добавлено не будет - set  хранит только уникальные значения
//а вот  multiset добавит

mySet.insert(4);
print(mySet);


// Поиск элемента - метод find
for (int i=0;i<100;++i){
 mySet.insert(rand()%1000 );
}

print(mySet);

auto it=mySet.find(200); // в случае успеха - возвращает итератор а в случае если элемента нет
// вернет итератор mySet(end)

int value = 778;
if (mySet.find(value) != mySet.end()){
 cout<<"element finding "<<endl;
}
else {
  cout<<"no elements finding"<<endl;
}

//Удаление - метод erase
mySet = {1,44,6,13,666,-34,-2,43};
print(mySet);
mySet.erase(13);
print(mySet);

// метод erase при успешном удалении возвращает 1  а при неуспешном - 0 (если элемента не было)
// то же и insert - возвращает 2 значения - итератор и bool переменную


multiset<int> myMultiset = {1,66,16,48,99};
cout<<"multiset"<<endl;
print2(myMultiset);
myMultiset.insert(66);
myMultiset.insert(66);
myMultiset.insert(66);
print2(myMultiset);

auto it1 = myMultiset.lower_bound(66);  // метод вернет итератор на первое число 66
cout<<*it1<<endl;
auto it2 = myMultiset.upper_bound(66);  // метод вернет итератор на следующее число после 66
cout<<*it2<<endl;

auto it3 = myMultiset.upper_bound(99); //тут возвращается уже мусор !!!
cout<<*it3<<endl;

auto a = myMultiset.equal_range(66); //возвращает диапазон от lower_bound до upper_bound
// то есть 2 итератора

return 0 ;
 }
