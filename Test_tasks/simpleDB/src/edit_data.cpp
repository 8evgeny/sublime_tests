#include "simpleDB.h"
using namespace std;
void edit_data(){
    string iname;
    Person person;
    system("clear");
    std::cout<<"\nРедактируем существующую запись в БД:\n";
    read_data();
    cout<<"введите имя персоны:\n";
    while(1){
        cin>>iname;
        regex regexpr ("[A-Za-z]+");
        if (regex_match (iname,regexpr)) {
            person.read_person(iname);
            break;
        } else  cout << "Введите корректное имя!\n";
    }
    cout<<"Выводим данные о персоне:\n";
    person.print();




};
