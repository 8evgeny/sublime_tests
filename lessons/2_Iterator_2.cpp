#include <iostream>
#include <vector>  // Подключаем
using namespace std;
 // Константные итераторы
int main()
{
    setlocale(LC_ALL,"ru");
vector<int> myVector = { 5,9,44,422,676,78,-38,55,-345,2,5687,3 };


//for (vector<int>::const_iterator i=myVector.begin(); i != myVector.end(); i++ )// !!!!!!!!!
// begin  end  будут работать благодаря наследованию и полиморфизму но лучше так :
    for (vector<int>::const_iterator i=myVector.cbegin(); i != myVector.cend(); i++ )
{
 //*i = 5;   - не сработает !!!!!!!!!!!!!!
cout<< *i <<endl;
}
 cout<<endl;
 cout<<"From end to begin"<<endl;
//Итерирование с конца в начало
    for (vector<int>::reverse_iterator i=myVector.rbegin(); i != myVector.rend(); i++ )
{
cout<< *i <<endl;
}
 cout<<endl;
vector<int>::iterator it =myVector.begin();
// Для контейнеров у которых итераторы не поддерживают арифметику указателей есть функция
advance(it,3); // сдвигаем итератор на 3 элемента
cout<< *it <<endl;

cout<<"insert"<<endl;
// Возвращаемся к вектору 2 метода insert b erase
vector<int>::iterator itt =myVector.begin();
myVector.insert(itt,999);   //Вставилось на 0 позицию - 1 элемент
        for (vector<int>::iterator i=myVector.begin(); i != myVector.end(); i++ )
    {
    cout<< *i <<endl;
    }
  cout<<endl;

 vector<int>::iterator it2 =myVector.begin();
 advance(it2,5);
 myVector.insert(it2,1999);   //Вставилось на 5 позицию - 6 элемент  !!!!!!!!!!!
 for (vector<int>::iterator j=myVector.begin(); j != myVector.end(); j++ )
{
cout<< *j <<endl;
}
  cout<<"erase"<<endl;
 vector<int>::iterator it3 =myVector.begin();
 for (vector<int>::iterator j=myVector.begin(); j != myVector.end(); j++ )
{
cout<< *j <<endl;
}
   cout<<endl;
advance(it3,3); //Удалять будем элемент с индексом 3

 myVector.erase(it3); //Удалили 44
myVector.erase(it3+2,it3+4); //Удалили 676 и 78   !!!!!!!!!!!!!!
 for (vector<int>::iterator j=myVector.begin(); j != myVector.end(); j++ )
{
cout<< *j <<endl;
}
  cout<<endl;

return 0 ;
}

