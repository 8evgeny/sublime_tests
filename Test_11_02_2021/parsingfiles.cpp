#include "parsingfiles.h"

#include <boost/filesystem/operations.hpp>
#include <boost/lexical_cast.hpp>
#include <fstream>
using namespace std;
namespace bf = boost::filesystem;

struct ParsingFiles::Impl {
  Impl();

  vector<string> ReadDir(string);
  void PrintDir(vector<string> v);
  void ReadFile();
  void ReadSeparators();

  vector<string> listfiles;
  vector<string> listseparators;
};
ParsingFiles::Impl::Impl() {}
ParsingFiles::ParsingFiles() : _d{make_unique<Impl>()} {}
ParsingFiles::~ParsingFiles() {}

void ParsingFiles::ParsingDir(string p) {
  vector<string> v = _d->ReadDir(p);
  _d->PrintDir(v);
  _d->ReadSeparators();
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

void ParsingFiles::Impl::PrintDir(vector<string> vdir) {
  cout << "Парсятся следующие файлы: " << endl;
  for (auto& filename : vdir) {
    cout << filename << endl;
  }
  cout << endl;
}

void ParsingFiles::Impl::ReadSeparators() {
  fstream f("../separators.ini", ios::in | ios::binary);
  string s;
  cout << "Для парсинга содержимого файлов используются следующие сепараторы: "
       << endl;
  while (f >> s) {
    listseparators.push_back(s);
    cout << s << endl;
  }
  cout << endl;
};
