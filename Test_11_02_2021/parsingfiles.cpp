#include "parsingfiles.h"

#include <string.h>

#include <boost/filesystem/operations.hpp>
#include <boost/lexical_cast.hpp>
#include <cstddef>
#include <cstring>
#include <fstream>
using namespace std;
namespace bf = boost::filesystem;

struct ParsingFiles::Impl {
  Impl();
  vector<string> ReadDir(string);
  void PrintDir(vector<string>&);
  pair<string, vector<string>> ReadSingleFile(string&);
  vector<string> ParsingSingleFile(pair<string, vector<string>>&);

  vector<string> listfiles;
  list<string> listseparators;
  vector<vector<string>> result;
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
    vector<string> result_parsing_single_file =
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

vector<string> ParsingFiles::Impl::ParsingSingleFile(
    pair<string, vector<string>>& pair) {
  string in = pair.first;
  vector<string> res;
  auto i = pair.second.begin();  // i - разделитель с которым работаем
  //  for (; i != pair.second.end();) {  //по разделителям
  cout << "Ищем разделитель: " << *i << endl;

  std::size_t pos = in.find(*i);
  if (pos != std::string::npos) {
    //  auto pos = search(pair.first.begin(),
    //                    pair.first.end(),           // range
    //                    (*i).begin(), (*i).end());  // subrange

    //  if (pos != pair.first.end()) {
    cout << "Разделитель найден:" << endl;
    //делим text на 2 строки и вторую пушим
    string newtext(in, pos);
    newtext.replace(
        newtext.begin(), newtext.begin() + (*i).length(),
        "");  // newtext - Новая строка без разделителя для дальнейшего парсинга
    string s;
    s.assign(in, pos);
    //    copy(pair.first.begin(), pos, s);
    int a = (*i).length();
    //    s.replace(s.length() - a, s.end(), " ");
    res.push_back(newtext);
    //    cout << pair.first << endl;
    cout << "Новая строка без разделителя: " << endl << newtext << endl << endl;
    //удаляем из text найденную часть(до разделителя)
    //
    //Удаляем сам разделитель
    //
    //    cout << pair.first << endl;
  } else {
    cout << "Разделитель не найден:" << endl << endl;
    //разделитель (*i) в строке не найден
    //переходим к следующему разделителю
    ++i;
  }
  //
  //  }  //по разделителям
  return res;
}
