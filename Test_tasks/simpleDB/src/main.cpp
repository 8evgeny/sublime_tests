#include "simpleDB.h"
using namespace std;
//Регулярку даты доработать

int main(int argc, char** argv) {

    Person person;
    string name = "aa";
    QSettings settings(settingsFile, QSettings::IniFormat);
    settings.beginGroup("person");
    QString patch_to_DB = settings.value("patch_to_DB").toString();
    settings.endGroup();
    //полный путь к файлу
    string path = patch_to_DB.toStdString()+"/"+name;
    ifstream file;
    file.open(path,ofstream::binary);
    if(!file.is_open()) cout<<"ошибка открытия файла\n";
    else{
        int size;
        file.read((char*)&size, sizeof (int));
        while(!file.eof()){
        file.read((char*)&person, size);
        }

            cout<<"Данные успешно прочитаны из файла: "<< name<<"\n";
    }
    file.close();
    person.print();

// string oper ="0";
// while(1){
//  cout<<"Введите операцию:\n"<<
//        "1 - отображение существующих записей:\n"<<
//        "2 - ввод новых данных:\n"<<
//        "3 - редактирование данных:\n"<<
//        "4 - завершить работу:\n";
//  cin>>oper;
//  regex regexpr ("[1234]");
//  if (regex_match (oper,regexpr)) {
//  if(oper == "1") read_data();
//  if(oper == "2") input_data();
//  if(oper == "3") edit_data();
//  if(oper == "4") return 0;
//  } else cout<<"Повторите ввод\n\n";
// }

}




