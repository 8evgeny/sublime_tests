#include "simpleDB.h"
using namespace std;
void print_nation(vector<pair<unsigned,string>>&nations){
    QSettings settings(settingsFile, QSettings::IniFormat);
    settings.beginGroup("nationDIR");
    QString patch_to_nation = settings.value("patch_to_nation").toString();
    settings.endGroup();
    string path = patch_to_nation.toStdString()+"/nations";
    ifstream is(path.c_str());
    char c;
    string stchar;
    pair<unsigned,string> p;
    unsigned i = 1;
    while (!is.eof()){
        is.get(c);
        if(c!='\n')stchar.push_back(c);
        if(c =='\n'){
      pair<unsigned,string> p(i,stchar);
      if(p.second !="")nations.push_back(p);
      stchar.clear();
      ++i;
      }
    }
    is.close();
    print_vector(nations);


    cout<<'\n';



}
