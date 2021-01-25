#include "simpleDB.h"
#include "person.h"
using namespace std;
void input_death(Person & person){
 string ideath;
//Дата смерти
 cout<< "\nВведите дату смерти в формате DD/MM/YYYY или DD-MM-YYYY:\n";
 const QString DateFormat = "dd/MM/yyyy";
 QDate death, current;
 while(1){
  cin>>ideath;
  regex regexpr (
"(0[1-9]|[12][0-9]|3[01])[/](0?[1-9]|1[12])[/](1[0-9][0-9]{2}|[2][0][0-9]{2})"
  );
  if (regex_match (ideath,regexpr)) {
   string day = ideath.substr(0,2);
   string mounth = ideath.substr(3,2);
   string year = ideath.substr(6,4);
   death.setDate(stoi(year),stoi(mounth),stoi(day));
   current=QDate::currentDate();
   QDate bithday = person.bithday;
   int days_from_bithday = bithday.daysTo(death);
   int days_to_current = death.daysTo(current);
   if((days_from_bithday>0) &&(days_to_current>0)){
    person.death = death;
    break;
   } else  cout << "Введите корректную дату!\n";
  } else  cout << "Введите корректную дату!\n";
 }
 cout<<"Введена дата смерти: "<<person.death.toString(DateFormat).toStdString()<<"\n";
}
