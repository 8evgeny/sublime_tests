#include "simpleDB.h"
using namespace std;
void edit_data(){
    QSettings settings(settingsFile, QSettings::IniFormat);
    settings.beginGroup("person");
    int max_long_life  = settings.value("max_long_life").toInt();
    int max_growth  = settings.value("max_growth").toInt();
    int max_weight  = settings.value("max_weight").toInt();
    settings.endGroup();


    string iname;
    Person person;
    system("clear");
    cout<<"\nРедактируем существующую запись в БД:\n";
    read_data();
    cout<<"введите имя персоны:\n";
    while(1){
        cin>>iname;
        regex regexpr ("[A-Za-z]+");
        if (regex_match (iname,regexpr)) {
            read_person(person,iname);
            break;
        } else  cout << "Введите корректное имя!\n";
    }
    cout<<"Выводим данные о персоне:\n";
    person.print();
 cout<<"введите номер записи для редактирования: \n";
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
   if(stoi(num)==4) person.input_growth(max_growth);
   if(stoi(num)==5) person.input_weight(max_weight);
   if(stoi(num)==6) person.input_nation();
   if(stoi(num)==7) {
       person.input_bithday();



   }
   if(stoi(num)==8) {
       person.input_death();



   }
  person.save_person();
   break;
        }else  cout << "Введите корректный номер!\n";
        }








}






