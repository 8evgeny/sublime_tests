#include "simpleDB.h"
#include "person.h"

using namespace std;

void input_data(){
 system("clear");
 Person person;
 cout<<"Вводим новые данные:\n";
 cout<<"\nВведите имя латиницей:\n";
 string iname, isex, ibighday, igrowth, iweight, ideath;
//Имя
 while(1){
  cin>>iname;
  regex regexpr ("[A-Za-z]+");
  if (regex_match (iname,regexpr)) {
     person.name = iname;
     break;
  } else  cout << "Введите корректное имя!\n";
 }
 cout << "Введено имя: "<<person.name<<"\n"<<
      "\nВведите пол:\n"<<"1 - мужчина\n"<<"2 - женщина\n";
//Пол
 while(1){
  cin>>isex;
   regex regexpr ("[12]");
  if (regex_match (isex,regexpr)) {
     person.sex = stoi(isex);
     break;
  } else  cout << "Введите корректный пол!\n";
 }
 cout << "Введен пол: "<<person.sex<<"\n"<<
     "\nВведите дату рождения в формате DD/MM/YYYY или DD-MM-YYYY:\n";

 //Дата рождения
 const QString DateFormat = "dd/MM/yyyy";
 while(1){
  cin>>ibighday;
  regex regexpr (
 "(0?[1-9]|[12][0-9]|3[01])[/ -](0?[1-9]|1[12])[/ -](19[0-9]{2}|[2][0-9][0-9]{2})"
 );
  if (regex_match (ibighday,regexpr)) {
   string day = ibighday.substr(0,2);
   string mounth = ibighday.substr(3,2);
   string year = ibighday.substr(6,4);
   QDate date;
   date.setDate(stoi(year),stoi(mounth),stoi(day));
   person.bithday = date;
   break;
  } else  cout << "Введите корректную дату!\n";
 }
 cout<<"введена дата: "<<
 person.bithday.toString(DateFormat).toStdString()<<"\n"
 //Рост
 << "\nВведите рост в сантиметрах: \n";
 while(1){
     cin>>igrowth;
     regex regexpr ("[0-9][0-9][0-9]");
     if (regex_match (igrowth,regexpr)) {
         person.growth = stoi(igrowth);
         break;
     } else  cout << "Введите корректный рост!\n";
 }
 cout << "Введен рост: "<<person.growth<<"\n"<<
     "\nВведите национальность. Выберите номер из списка:\n";



};
