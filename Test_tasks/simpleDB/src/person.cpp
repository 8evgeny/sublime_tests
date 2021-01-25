#include "simpleDB.h"
#include "person.h"
using namespace std;
 Person::Person(){
     live=true;};
// Person::Person (string name,
//                string sex,
//                unsigned age,
//                unsigned growth,
//                unsigned weight,
//                string nation,
//                QDate bithday):
// name(name),sex(sex),age(age),growth(growth),weight(weight),nation(nation),bithday(bithday) {live=true;};
 Person::~Person(){};

 void Person::print(){
     std::cout
         <<"1\tИмя: "<<name.toStdString()<<"\n"
         <<"2\tПол: "<<sex.toStdString()<<"\n"
         <<"3\tВозраст: "<<age<<"\n"
         <<"4\tРост: "<<growth<<"\n"
         <<"5\tВес: "<<weight<<"\n"
         <<"6\tНациональность: "<<nation.toStdString()<<"\n"
         <<"7\tДата рождения: "<<Person::bithday.toString().toStdString()<<"\n"
         <<"8\tДата смерти: "<<Person::death.toString().toStdString()<<"\n"
         <<"\n";
 }
 void Person::save_person(Person & person){
     QSettings settings(settingsFile, QSettings::IniFormat);
     settings.beginGroup("person");
     QString patch_to_DB = settings.value("patch_to_DB").toString();
     settings.endGroup();
     //полный путь к файлу
     string path = patch_to_DB.toStdString()+"/"+person.name.toStdString();
     fstream file;
     file.open(path, fstream::app | fstream::out | fstream::in | fstream::binary);
     if(!file.is_open()) cout<<"ошибка открытия файла\n";
     else{
//         int size = sizeof (person);
//         cout<<"размер: "<<size<<endl;
//         file.write((char*)&size, sizeof (int));
//         file.write((char*)&person, size);
//QString name;
//QString sex;
//unsigned age;
//unsigned growth;
//unsigned weight;
//QString nation;
//QDate bithday;
//QDate death;
//bool live;
const QString DateFormat = "dd/MM/yyyy";
        file<<person.name.toStdString()<<"\n";
        file<<person.sex.toStdString()<<"\n";
        file<<person.age<<"\n";
        file<<person.growth<<"\n";
        file<<person.weight<<"\n";
        file<<person.nation.toStdString()<<"\n";
        file<<person.bithday.toString(DateFormat).toStdString()<<"\n";
        if (!person.live) file<<person.death.toString(DateFormat).toStdString()<<"\n";
        if (person.live) file<<"no"<<"\n";
        file<<person.live<<"\n";
         cout<<"Данные успешно сохранены в файле: "<< person.name.toStdString()<<"\n";
     }
     file.close();
 }
 void Person::input_name(){
     cout<<"\nВведите имя латиницей:\n";
     string iname;
      while(1){
       cin>>iname;
       regex regexpr ("[A-Za-z]+");
       if (regex_match (iname,regexpr)) {
           this->name = QString::fromStdString(iname);
          break;
       } else  cout << "Введите корректное имя!\n";
      }
      cout << "Введено имя: "<<this->name.toStdString()<<"\n";
 }
 void Person::input_sex(){
  string isex;
 cout <<"\nВведите пол:\n"<<"1 - мужчина\n"<<"2 - женщина\n";
//Пол
 while(1){
  cin>>isex;
   regex regexpr ("[12]");
  if (regex_match (isex,regexpr)) {
       if(stoi(isex)==1)this->sex = "male";
       else this->sex = "female";
     break;
  } else  cout << "Введите корректный пол!\n";
 }
 cout << "Введен пол: "<<this->sex.toStdString()<<"\n";
 }
 void Person::input_bithday(){
  string ibighday;
 cout<<   "\nВведите дату рождения в формате DD/MM/YYYY или DD-MM-YYYY:\n";
//Дата рождения
const QString DateFormat = "dd/MM/yyyy";
while(1){
 cin>>ibighday;
 regex regexpr (
"(0[1-9]|[12][0-9]|3[01])[/](0?[1-9]|1[12])[/](1[0-9][0-9]{2}|[2][0][0-9]{2})"
);
 if (regex_match (ibighday,regexpr)) {
  this->bithday = string_toqtate(ibighday);
  break;
 } else  cout << "Введите корректную дату!\n";
}
 cout<<"введена дата: "<<
    this->bithday.toString(DateFormat).toStdString()<<"\n";
}
 void Person::input_death(){
      string ideath;
      cout<< "\nВведите дату смерти в формате DD/MM/YYYY:\n";
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
        QDate bithday = this->bithday;
        int days_from_bithday = bithday.daysTo(death);
        int days_to_current = death.daysTo(current);
        if((days_from_bithday>0) &&(days_to_current>0)){
         this->death = death;
         break;
        } else  cout << "Введите корректную дату!\n";
       } else  cout << "Введите корректную дату!\n";
      }
      cout<<"Введена дата смерти: "<<this->death.toString(DateFormat).toStdString()<<"\n";
 }
