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

void read_person(Person & person, string & name){
    QSettings settings(settingsFile, QSettings::IniFormat);
    settings.beginGroup("person");
    QString patch_to_DB = settings.value("patch_to_DB").toString();
    settings.endGroup();
    //полный путь к файлу
    string path = patch_to_DB.toStdString()+"/"+name;
    ifstream file;
    file.open(path, ios::app | ios::out | ios::in | ios::binary);
    if(!file.is_open()) cout<<"ошибка открытия файла\n";
    else{
        int size;
        while(!file.eof()){

        file.read((char*)&size, sizeof (int));
        file.read((char*)&person, size);

        }

            cout<<"Данные успешно прочитаны из файла: "<< name<<"\n";
    }
    file.close();
}


