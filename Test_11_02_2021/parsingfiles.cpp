#include "parsingfiles.h"

#include <algorithm>
#include <boost/filesystem/operations.hpp>
#include <boost/lexical_cast.hpp>
#include <cstddef>
#include <deque>
#include <fstream>
using namespace std;
namespace bf = boost::filesystem;

struct ParsingFiles::Impl {
  Impl();
  vector<string> ReadDir(string);
  void PrintDir(vector<string>&);
  string ReadSingleFile(string&);
  void ReadSeparators();
  deque<string> ParsingString(string&, list<string>&);

  vector<string> listfiles;
  list<string> listseparators;
  vector<deque<string>> result;
};
ParsingFiles::Impl::Impl() {}
ParsingFiles::ParsingFiles() : _d{make_unique<Impl>()} {}
ParsingFiles::~ParsingFiles() {}

void ParsingFiles::ParsingDir(string dir, string outfile) {
  vector<string> v = _d->ReadDir(dir);  //Читаем директорию
  _d->PrintDir(v);       //Печатаем список файлов
  _d->ReadSeparators();  //Получаем разделители из файла
  for (auto& file : _d->listfiles) {  //Парсим в цикле  все файлы
    string data_from_file = _d->ReadSingleFile(file);
    deque<string> result_parcing_single_file =
        _d->ParsingString(data_from_file, _d->listseparators);
    _d->result.push_back(result_parcing_single_file);
  }
}

vector<string> ParsingFiles::Impl::ReadDir(string pathdir) {
  bf::directory_iterator p(pathdir);
  for (bf::directory_entry& x : bf::directory_iterator(p)) {
    bf::file_status f = x.status();
    if (f.type() == bf::regular_file) {
      listfiles.push_back(boost::lexical_cast<string>(x));
    }
  }
  return listfiles;
}

void ParsingFiles::Impl::PrintDir(vector<string>& vdir) {
  cout << "Файлы для парсинга: " << endl;
  for (auto& filename : vdir) {
    cout << filename << endl;
  }
  cout << endl;
}

void ParsingFiles::Impl::ReadSeparators() {
  fstream f("../separators.ini", ios::in | ios::binary);
  string s;
  cout << "Для парсинга содержимого файлов используются следующие разделители: "
       << endl;
  while (f >> s) {
    listseparators.push_back(s);
    cout << s << endl;
  }
  cout << endl;
};

string ParsingFiles::Impl::ReadSingleFile(string& fileName) {
  string s;
  ifstream in(fileName, ios::in | ios::binary);
  while (!in.eof()) {
    char c = in.get();
    s.push_back(c);
  }
  return s;
}

deque<string> ParsingFiles::Impl::ParsingString(string& text,
                                                list<string>& sep) {
  deque<string> res;
  res.push_back(text);  //входную строку в дек
  int k = 0;  //номер обрабатываемой строки в деке

  for (auto& x : sep) {  //по разделителям
    cout << "Разделитель: " << x << endl;

    auto pos = search(res[k].begin(), res[k].end(),  // range
                      x.begin(), x.end());           // subrange

    if (pos != res[k].end()) {  // делим res[0] на 2 строки и вторую пушим
                                //Изменить цикл с диапазонного на обычный при
                                //нахождении pos --i при ненахождении pos i не
                                //меняем - переходим на следующий разделитель
    }
    //
  }  //по разделителям
  return res;
}
