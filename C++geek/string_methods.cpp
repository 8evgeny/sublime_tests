#include <string>
#include <iostream>

using std::cout;
using std::endl;
using std::string;

int main(){
    string s = "Hello word!  ";
    string t = "C++";
    cout<<"Длина строки - "<<s.size()<<endl;
    cout << std::boolalpha<<s.empty()<<endl; //Returns true if the string is empty.
    s.push_back('$');
    cout<<s<<endl;
    s.append(2, '_');
    s.append(4, '\'');
    cout<<s<<endl;
    s.append(t);
    cout<<s<<endl;
    s.append(t, 1, 2);
    cout<<s<<endl;
    s.clear();
    cout<<s<<endl;

    s = "Hello word!  ";
    s.erase(4);         //Удалить все с 4 символа
    cout<<s<<endl;
    s = "Hello word";
    s.erase(4, 3);      //Удалить с 4 символа 3 символа
    cout<<s<<endl;
    s.insert(2,3,'p');
    cout<<s<<endl;
    s.insert(2,t);
    cout<<s<<endl;
    s.insert(2,t,1,1);
    cout<<s<<endl;
    string s1 = s.substr(8); //Удаляет первые 8 символов
    cout<<s1<<endl;
    s1 = s.substr(4, 3); //Удаляет первые 4 и оставляет 3 символа
    cout<<s1<<endl;

    s = "Hello word!  ";
    string str = "Hello";
    s.replace(2,3,4,'f');
    cout<<s<<endl;
}
