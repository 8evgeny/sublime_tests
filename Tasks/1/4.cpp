//Программа должна переводить число, введенное с клавиатуры в метрах, в километры.

#include <iostream>
using namespace std;
int main()
{
    cout<<"Перевод метров в километры"<<endl ;
    float m;
    cout<<"Введите количество метров: ";
    cin>>m;
    cout<< "Это "<<m/1000<<" километрa"<<endl;
    return 0;
}
