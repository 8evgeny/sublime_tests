#include "simpleDB.h"
#include "person.h"
using namespace std;
void input_data(){
 system("clear");
 Person person;
 auto max = person.read_max();
 cout<<"Вводим новые данные:\n";
 person.input_name();
 person.input_sex();
 person.input_bithday();
 QDate current_date;
 current_date=QDate::currentDate();
 cout<<"Текущая дата: "<<current_date.toString().toStdString()<<"\n";

  int days = person.bithday.daysTo(current_date);
  int age = days/365;
  if (age>max.max_long_life) {
      person.live = false;
      person.input_death();
  }
 person.input_growth(max.max_growth);
 person.input_weight(max.max_weight);
 person.input_nation();
 string  ilive, isave;
 if(person.live){
      cout<<"введите 1 если человек жив или 2  если нет\n";
      while(1){
          cin>>ilive;
          regex regexpr ("[12]");
          if (regex_match (ilive,regexpr)) {
              if(stoi(ilive)==2){
                person.live = false;
                person.input_death();
              }
              break;
          } else  cout << "Введите корректный номер!\n";
      }
  }

  if (person.live) person.age = age;
  else{
      person.age = person.bithday.daysTo(person.death)/365;
  }
  system("clear");
  person.print();
  cout <<"Подтвердите правильность введенных данных:\n"
         "1 - сохранить данные в базе\n2 - не сохранять\n ";
  while(1){
      cin>>isave;
      regex regexpr ("[12]");
      if (regex_match (isave,regexpr)) {
          if(stoi(isave)==1) person.save_person();
          if(stoi(isave)==2) {
           person.live = true;
          }
       break;
      } else  cout << "Введите корректный номер!\n";
  }

}


