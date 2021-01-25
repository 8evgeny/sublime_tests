#include "simpleDB.h"
#include "person.h"
using namespace std;
void input_data(){
 system("clear");
 Person person;
 QSettings settings(settingsFile, QSettings::IniFormat);
 settings.beginGroup("person");
 int max_long_life  = settings.value("max_long_life").toInt();
 int max_growth  = settings.value("max_growth").toInt();
 int max_weight  = settings.value("max_weight").toInt();
 settings.endGroup();
 cout<<"Вводим новые данные:\n";
 cout<<"\nВведите имя латиницей:\n";
 string iname, isex, ibighday, igrowth, iweight, inations, ilive, isave;
//Имя
 while(1){
  cin>>iname;
  regex regexpr ("[A-Za-z]+");
  if (regex_match (iname,regexpr)) {
      person.name = QString::fromStdString(iname);
     break;
  } else  cout << "Введите корректное имя!\n";
 }
 cout << "Введено имя: "<<person.name.toStdString()<<"\n"<<
      "\nВведите пол:\n"<<"1 - мужчина\n"<<"2 - женщина\n";
//Пол
 while(1){
  cin>>isex;
   regex regexpr ("[12]");
  if (regex_match (isex,regexpr)) {
       if(stoi(isex)==1)person.sex = "male";
       else person.sex = "female";
     break;
  } else  cout << "Введите корректный пол!\n";
 }
 cout << "Введен пол: "<<person.sex.toStdString()<<"\n"<<
     "\nВведите дату рождения в формате DD/MM/YYYY или DD-MM-YYYY:\n";
//Дата рождения
 const QString DateFormat = "dd/MM/yyyy";
 QDate current_date;
 while(1){
  cin>>ibighday;
  regex regexpr (
 "(0[1-9]|[12][0-9]|3[01])[/](0?[1-9]|1[12])[/](1[0-9][0-9]{2}|[2][0][0-9]{2})"
 );
  if (regex_match (ibighday,regexpr)) {
   person.bithday = string_toqtate(ibighday);
   current_date=QDate::currentDate();
   cout<<"Текущая дата: "<<current_date.toString().toStdString()<<"\n";
   break;
  } else  cout << "Введите корректную дату!\n";
 }
  cout<<"введена дата: "<<
     person.bithday.toString(DateFormat).toStdString()<<"\n";
//Возраст
  int days = person.bithday.daysTo(current_date);
  int age = days/365;
  if (age>max_long_life) {
      person.live = false;
      input_death(person);
  }

//Рост
 cout<< "\nВведите рост в сантиметрах: \n";
 while(1){
     cin>>igrowth;
     regex regexpr ("[1-9]{1}[0-9]{0,2}");
     if (regex_match (igrowth,regexpr)) {
         if(stoi(igrowth)<=max_growth){
         person.growth = stoi(igrowth);
         break;
         } else  cout << "Введите корректный рост!\n";
     } else  cout << "Введите корректный рост!\n";
 }
 cout << "\nВведен рост: "<<person.growth<<"\n\n"
//Вес
 << "\nВведите вес в килограммах: \n";
 while(1){
     cin>>iweight;
     regex regexpr ("[1-9]{1}[0-9]{0,2}");
     if (regex_match (iweight,regexpr)) {
         if(stoi(iweight)<=max_weight){
         person.weight = stoi(iweight);
         break;
         } else  cout << "Введите корректный вес!\n";
     } else  cout << "Введите корректный вес!\n";
  }
 cout << "\nВведен вес: "<<person.weight<<"\n";
//Национальность
 vector <pair<unsigned,string>> listnations;
 print_nation(listnations);
 cout<<"\nВведите национальность. Выберите номер из списка:\n";
 while(1){
     cin>>inations;
     regex regexpr ("[1-9]{1}[0-9]{0,2}");
     if (regex_match (inations,regexpr)) {
         if (stold(inations) <= listnations.size()) {
         string nation = listnations.at(stoi(inations)-1).second;
         person.nation = QString::fromStdString(nation);
         break;
         } else  cout << "Введите корректный номер!\n";
     } else  cout << "Введите корректный номер!\n";
 }
  cout << "Выбрана национальность: "<<person.nation.toStdString()<<"\n";

  if(person.live){
      cout<<"введите 1 если человек жив или 2  если нет\n";
      while(1){
          cin>>ilive;
          regex regexpr ("[12]");
          if (regex_match (ilive,regexpr)) {
              if(stoi(ilive)==2){
                person.live = false;
                input_death(person);
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
         "1 - сохранить данные в базе\n2 - не сохранять ";
  while(1){
      cin>>isave;
      regex regexpr ("[12]");
      if (regex_match (isave,regexpr)) {
          if(stoi(isave)==1) person.save_person(person);
          if(stoi(isave)==2) {
           person.live = true;
          }
       break;
      } else  cout << "Введите корректный номер!\n";
  }

};//end void input_data()


