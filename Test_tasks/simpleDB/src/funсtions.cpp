#include "simpleDB.h"
using namespace std;
void fill_vector(QStringList& listFiles, vector<std::string>& v) {
    for (auto& file : listFiles) {
        v.push_back(file.toStdString());
    }
}

void print_vector(vector<string>& v) {
    int i = 1;
    for (auto element : v)  {
    cout<<i<<" "<<element<<'\n';
        ++i;
    }
    cout<<'\n';
}

void print_vector(vector<pair<unsigned,string>>& v) {

    for (auto element : v)  {
        cout<<element.first<<" "<<element.second<<'\n';
    }
    cout<<'\n';
}

QDate string_toqtate(string stringdate){
    QDate date;
    string day = stringdate.substr(0,2);
    string mounth = stringdate.substr(3,2);
    string year = stringdate.substr(6,4);
    date.setDate(stoi(year),stoi(mounth),stoi(day));
    return date;
}

void read_person(Person & person, string & name){
    QSettings settings(settingsFile, QSettings::IniFormat);
    settings.beginGroup("person");
    QString patch_to_DB = settings.value("patch_to_DB").toString();
    settings.endGroup();
    //полный путь к файлу
    string path = patch_to_DB.toStdString()+"/"+name;
    fstream file;
    file.open(path, fstream::app | fstream::out | fstream::in | fstream::binary);
    if(!file.is_open()) cout<<"ошибка открытия файла\n";
    else{
//        int size;
//        while(!file.eof()){
//            file>>(char*)&person;
//        file.read((char*)&size, sizeof (int));
//        file.read((char*)&person, size);
//        }

string name;
string sex;
string age;
string growth;
string weight;
string nation;
string bithday;
string death;
string live;
const QString DateFormat = "dd/MM/yyyy";
file>>name;
file>>sex;
file>>age;
file>>growth;
file>>weight;
file>>nation;
file>>bithday;
file>>death;
file>>live;
//cout<<"name: "<<name<<"\n"
//<<"sex: "<<sex<<"\n"
//<<"age: "<<age<<"\n"
//<<"growth: "<<growth<<"\n"
//<<"weight: "<<weight<<"\n"
//<<"nation: "<<nation<<"\n"
//<<"bithday: "<<bithday<<"\n"
//<<"death: "<<death<<"\n"
//<<"live: "<<live<<"\n";
cout<<"Данные успешно прочитаны из файла: "<< name<<"\n";
person.name = QString::fromStdString(name);
person.sex = QString::fromStdString(sex);
person.age = stoi(age);
person.growth = stoi(growth);
person.weight = stoi(weight);
person.nation = QString::fromStdString(nation);
person.bithday = string_toqtate(bithday);
person.live = stoi(live);
if(person.live == 0) person.death = string_toqtate(death);
    }
    file.close();
}

void delete_file(QString & name){
    QSettings settings(settingsFile, QSettings::IniFormat);
    settings.beginGroup("person");
    QString patch_to_DB = settings.value("patch_to_DB").toString();
    settings.endGroup();
    //полный путь к файлу
    string path = patch_to_DB.toStdString()+"/" + name.toStdString();
    string command = "rm " + path;
    system(command.c_str()); //удаление файла
}
