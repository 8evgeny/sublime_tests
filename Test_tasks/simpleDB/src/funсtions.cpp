#include "simpleDB.h"

void fill_vector(QStringList& listFiles, std::vector<std::string>& v) {
    for (auto& file : listFiles) {
        v.push_back(file.toStdString());
    }
}

void print_vector(std::vector<std::string>& v) {
    int i = 1;
    for (auto element : v)  {
        std::cout<<i<<" "<<element<<'\n';
        ++i;
    }
}
