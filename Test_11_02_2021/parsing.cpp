#include <boost/filesystem/operations.hpp>
#include <boost/lexical_cast.hpp>
#include <deque>
#include <fstream>

#include "main.h"
using namespace std;
namespace bf = boost::filesystem;
struct ParsingFiles::Impl {
  Impl();
  vector<string> ReadDir(string);
  void PrintDir(vector<string>&);
  pair<string, vector<string>> ReadSingleFile(string&);
  deque<string> ParsingSingleFile(pair<string, vector<string>>&, string&,
                                  string&);

  vector<string> listfiles;
  vector<deque<string>> result;
};
ParsingFiles::Impl::Impl() {}
ParsingFiles::ParsingFiles() : _d{make_unique<Impl>()} {}
ParsingFiles::~ParsingFiles() {}

//######## логика парсинга ##################################
void ParsingFiles::ParsingDir(string dir, string outfile) {
  vector<string> v = _d->ReadDir(dir);  //Читаем директорию
  _d->PrintDir(v);  //Печатаем список файлов

  for (auto& file : _d->listfiles) {  //Парсим в цикле  все файлы
    pair<string, vector<string>> data_from_file = _d->ReadSingleFile(file);
    deque<string> result_parsing_single_file =
        _d->ParsingSingleFile(data_from_file, file, outfile);
    _d->result.push_back(result_parsing_single_file);
  }
}
//#############################################################

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
  //  cout << "строка для парсинга: " << endl << input_string << endl;
  //  cout << "разделители: " << endl;
  //  for (auto& x : separators) cout << x << endl;
  //  cout << endl;
  return p;
}

//######## парсинг одного файла ##################################
deque<string> ParsingFiles::Impl::ParsingSingleFile(
    pair<string, vector<string>>& pair, string& name, string& outfile) {
  deque<string> res{};
  res.push_back(pair.first);
  for (auto i = pair.second.begin(); i != pair.second.end();
       ++i) {  // i - разделитель с которым работаем
               //    cout << "Ищем разделитель: " << *i << endl;
    bool a = true;
    unsigned long k = 0;  //элемент дека с которым работаем
    auto it = res.begin();
    while (a) {
      auto pos = res[k].find(*i);  //ищем разделитель
      if (pos != std::string::npos) {
        //        cout << "Разделитель найден:" << endl;
        //делим text на 2 строки ту что после разделителя пушим в дек а исходную
        //укорачиваем
        string s(res[k],
                 pos + (*i).length());  // s - то что осталось после разделителя
        res[k].erase(pos);  // остается короткая строка до разделителя
        //        cout << "в деке: " << res.size() << endl;
        //        cout << "k: " << k << endl;

        it = res.begin();
        advance(it, k + 1);
        res.insert(it, s);
      } else {
        //        cout << "Разделитель не найден:" << endl << endl;
        if (k < res.size() - 1) {  //к следующей строке дека
          ++k;
        } else {
          a = false;
        }
      }
    }  // end while
  }    // for по разделителям

  // запись в файл
  fstream out(outfile, ios::out | ios::app);
  cout << "[Имя файла " << name << " ]:" << endl;
  out << "[Имя файла " << name << " ]:" << endl;
  int i = 0;
  for (auto& x : res) {
    ++i;
    cout << "Подстока " << i << " файла " << name << ": " << x << endl;
    out << "Подстока " << i << " файла " << name << ": " << x << endl;
  }
  cout << endl;
  out << endl;

  return res;
}
//#############################################################
//
