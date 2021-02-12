#include "parsingfiles.h"

#include <algorithm>
#include <boost/filesystem/operations.hpp>
#include <boost/lexical_cast.hpp>
#include <fstream>
using namespace std;
namespace bf = boost::filesystem;

struct ParsingFiles::Impl {
  Impl();
  vector<string> ReadDir(string);
  void PrintDir(vector<string>&);
  string ReadSingleFile(string&);
  void ReadSeparators();
  vector<string> ParsingString(string&, vector<string>&);

  vector<string> listfiles;
  vector<string> listseparators;
  vector<vector<string>> result;
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
    vector<string> result_parcing_single_file =
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

vector<string> ParsingFiles::Impl::ParsingString(string& text,
                                                 vector<string>& sep) {
  vector<string> result_parsing_string;
  string::iterator pos = find_first_of(text.begin(), text.end(),  // range
                                       sep.begin(), sep.end());   // subrange
                                                                  //
  //
  return result_parsing_string;
}
