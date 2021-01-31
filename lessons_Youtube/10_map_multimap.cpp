#include <iostream>
#include <string>
#include <QString>
#include <map>
#include <random>
#include <ctime>
#include <algorithm>
using namespace std;

void print(const map<int,int> &name);

int main()
{

    QString tmp ="PrimerString";
    tmp.append("123") ;

    cout<<QString (5,tpm);
    cout<<tmp.toStdString();

pair <int , string> p;  // пара любых типов данных
p.first = 1;
p.second = "телефон";

// или так
pair <int, string> p2(8, "telephone");
//cout<<p2.first<<" "<<p2.second<<endl;

map <int, string> myMap;

// insert  принимает готовую пару либо используем метод make_pair
myMap.insert(make_pair(11,"Nokia"));
myMap.insert(pair<int,string>(1,"some data"));
myMap.insert(p2);

// Метод emplace - можно добавить нужные элементы через запятую !!!
myMap.emplace(3,"sis");
myMap.emplace(7,"lol");

    for (auto element:myMap){
//        cout<<" "<<element.first<<" - "<<element.second<<", ";
    }
cout<<endl;
//Пример из моего теста(изменен)
//Создаем map и заполняем рандомными значениями от 1 до 100


std::mt19937 gen(static_cast<unsigned int>(time(nullptr)));
std::uniform_int_distribution<> randomDigit(1, 100);

int sizeMap = 20;
map <int,int> collMap;
    for (int i=1; i<=sizeMap; ++i)
    {
    collMap.emplace(i,randomDigit(gen));
    }
print(collMap);

//reverse(collMap.begin(),collMap.end()); - так не работает

print(collMap);
system("pause");
return(0);
 }

    void print(const std::map<int,int> &name)
    {
    std::cout<<"\n";
    for(auto element:name){
//        std::cout<<" Key: "<<element.first<<"  Value: "<<element.second<<"\n";
    }
//     std::cout<<"\n";
    };
