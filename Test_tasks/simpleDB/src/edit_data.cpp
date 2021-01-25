#include "simpleDB.h"
using namespace std;
void edit_data(){
    QSettings settings(settingsFile, QSettings::IniFormat);
    settings.beginGroup("person");
    int max_long_life  = settings.value("max_long_life").toInt();
    int max_growth  = settings.value("max_growth").toInt();
    int max_weight  = settings.value("max_weight").toInt();
    settings.endGroup();

    unsigned i;
    string inum;
    Person person;
    system("clear");
    cout<<"\nРедактируем существующую запись в БД:\n";
    unsigned number_person = read_data();
    cout<<"введите номер поля для редактирования:\n";

    while(1){
        cin>>inum;
        regex regexpr ("[0-9]+");
        if (regex_match (inum,regexpr)) {
            i = stoi(inum);
            if((i < number_person) && (i > 0)) {
                break;
            }else cout << "Введите корректный номер!\n";
        } else  cout << "Введите корректный номер!\n";
    }
    // i - номер записи для показа
    string name = name_from_munber(i);
    person.read_person(name);

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






