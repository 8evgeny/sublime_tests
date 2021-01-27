#include "simpleDB.h"
using namespace std;
void edit_data(){
    Person person;
    auto max = person.read_max();
    unsigned i;
    string inum;
    system("cls");
    cout<<"\nediting existing person:\n";
    while(1){
    unsigned number_person = read_data();
    cout<<"input number:\n"<<
        "to exit input 0\n";
    while(1){
        cin>>inum;
        regex regexpr ("[0-9]+");
        if (regex_match (inum,regexpr)) {
            i = stoi(inum);
            if((i <= number_person) && (i >= 0)) {
                break;
            }else cout << "incorrect!\n";
        } else  cout << "incorrect!\n";
    }
    if(i == 0)break;
    // i - номер записи для показа
    string name = name_from_munber(i);
    person.read_person(name);

    cout<<"print person:\n";
    person.print();
 cout<<"input number: \n";
 string num;
 while(1){
  cin>>num;
  regex regexpr ("[1245678]");
  if (regex_match (num,regexpr)) {
   if(stoi(num)==1) {
       QString old_name = person.name;
       delete_file(old_name);
       person.input_name();
       }
   if(stoi(num)==2) person.input_sex();
   if(stoi(num)==4) person.input_growth(max.max_growth);
   if(stoi(num)==5) person.input_weight(max.max_weight);
   if(stoi(num)==6) person.input_nation();
   if(stoi(num)==7) {
   person.input_bithday();
   QDate current_date=QDate::currentDate();
   int days = person.bithday.daysTo(current_date);
   int age = days/365;
    if (person.live) {
     if (age>max.max_long_life) {
         person.live = false;
         person.input_death();
      }
    }
   //меняем age
    if(person.live) person.age = person.bithday.daysTo(current_date)/365;
    else person.age = person.bithday.daysTo(person.death)/365;
   }
   if(stoi(num)==8) {
    person.input_death();
    person.age = person.bithday.daysTo(person.death)/365;
   }
  person.save_person();
   break;
        }else  cout << "incorrect!\n";
        }
    }

}






