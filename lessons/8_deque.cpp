
#include <iostream>
#include <deque>
using namespace std;
template<class T>
void print (const deque<T> &lst)
{
    for (auto i = lst.cbegin(); i !=lst.cend(); ++i) // !! Итерация префиксная
    {
     cout<<" "<<*i<<endl;
     }
}
int main()
{

deque<int> dq = {15,1,9,94};
auto it =dq.begin();
// методы аналогичны vector и  list


dq.push_front(5);
dq.push_back(55);
print(dq);



return 0 ;
 }
