#include "simpleDB.h"
#include "person.h"
#include <regex>
using namespace std;

void input_data(){
 Person person;
 cout<<"\nВводим новые данные:\n";
 cout<<"\nВведите имя латиницей:\n";
 string inputname;
 while(1){
  cin>>inputname;
  regex regexpr ("[A-Za-z]+");
  if (regex_match (inputname,regexpr)) {
     person.name = inputname;
     break;
  } else  cout << "Введите корректное имя!\n";
 }
 cout << "Введено имя: "<<person.name<<"\n";





};
