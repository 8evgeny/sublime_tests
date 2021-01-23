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




