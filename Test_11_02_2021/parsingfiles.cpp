#include "parsingfiles.h"

#include <string.h>

#include <boost/filesystem/operations.hpp>
#include <boost/lexical_cast.hpp>
#include <cstddef>
#include <cstring>
#include <deque>
#include <fstream>
using namespace std;
namespace bf = boost::filesystem;

struct ParsingFiles::Impl {
  Impl();
  vector<string> ReadDir(string);
  void PrintDir(vector<string>&);
  pair<string, vector<string>> ReadSingleFile(string&);
  deque<string> ParsingSingleFile(pair<string, vector<string>>&);

  vector<string> listfiles;
  list<string> listseparators;
  vector<deque<string>> result;
};
ParsingFiles::Impl::Impl() {}
ParsingFiles::ParsingFiles() : _d{make_unique<Impl>()} {}
ParsingFiles::~ParsingFiles() {}
//
//######## логика парсинга ##################################

void ParsingFiles::ParsingDir(string dir, string outfile) {
  vector<string> v = _d->ReadDir(dir);  //Читаем директорию
  _d->PrintDir(v);  //Печатаем список файлов

  for (auto& file : _d->listfiles) {  //Парсим в цикле  все файлы
    pair<string, vector<string>> data_from_file = _d->ReadSingleFile(file);
    deque<string> result_parsing_single_file =
        _d->ParsingSingleFile(data_from_file);
    _d->result.push_back(result_parsing_single_file);
  }
}
//#############################################################
//
vector<string> ParsingFiles::Impl::ReadDir(string pathdir) {
  bf::directory_iterator p(pathdir);
  for (bf::directory_entry& x : bf::directory_iterator(p)) {
    bf::file_status f = x.status();
    if (f.type() == bf::regular_file) {
      string s = boost::lexical_cast<string>(x);
      s.pop_back();
      s.replace(0, 1, "");
      listfiles.push_back(s);
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

pair<string, vector<string>> ParsingFiles::Impl::ReadSingleFile(
    string& fileName) {
  cout << "Читаем файл: " << fileName << endl;
  string input_string, sep;
  vector<string> separators;
  fstream in(fileName, ios::in | ios::binary);
  in >> input_string;  //строка для парсинга
  while (!in.eof()) {
    in >> sep;  //разделители
    separators.push_back(sep);
  }
  separators
      .pop_back();  //удаляем последний разделитель который записался дважды
  pair p = make_pair(input_string, separators);
  cout << "строка для парсинга: " << endl << input_string << endl;
  cout << "разделители: " << endl;
  for (auto& x : separators) cout << x << endl;
  cout << endl;
  return p;
}

deque<string> ParsingFiles::Impl::ParsingSingleFile(
    pair<string, vector<string>>& pair) {
  string s = pair.first;
  deque<string> res;
  res.push_back(pair.first);
  auto i = pair.second.begin();  // i - разделитель с которым работаем
  //  for (; i != pair.second.end();) {  //по разделителям
  cout << "Ищем разделитель: " << *i << endl;

  auto pos = res[0].find(*i);
  if (pos != std::string::npos) {
    cout << "Разделитель найден:" << endl;
    //делим text на 2 строки и обе кладем в дек а исходную удаляем
    string s1(s, pos + (*i).length());
    cout << "в деке: " << res.size() << endl;
    res.push_back(s1);
    s.erase(pos);
    res.push_back(s);
    res.pop_front();
    cout << "в деке: " << res.size() << endl;
    cout << "Новые строки: " << endl << s << endl << s1 << endl;
  } else {
    cout << "Разделитель не найден:" << endl << endl;

    if (i != pair.second.end()) {
      ++i;
    }
  }
  //
  //  }  //по разделителям
  return res;
}
