#include "parsingfiles.h"
using namespace std;
#define bf boost::filesystem
struct ParsingFiles::Impl {
  Impl();

  std::vector<bf::directory_entry> ReadDir(std::string);
  void PrintDir(std::vector<bf::directory_entry> v);
  void ReadFile();

  std::vector<bf::directory_entry> v;
};

ParsingFiles::Impl::Impl() {}

ParsingFiles::ParsingFiles() : _d{std::make_unique<Impl>()} {}

ParsingFiles::~ParsingFiles() {}

void ParsingFiles::ParsingDir(std::string p) {
  std::vector<bf::directory_entry> v = _d->ReadDir(p);
  _d->PrintDir(v);
}

std::vector<bf::directory_entry> ParsingFiles::Impl::ReadDir(
    std::string pathdir) {
  bf::directory_iterator p(pathdir);
  for (bf::directory_entry& x : bf::directory_iterator(p)) {
    bf::file_status f = x.status();
    if (f.type() == bf::regular_file) {
      v.push_back(x);
    }
  }
  return v;
}

void ParsingFiles::Impl::PrintDir(std::vector<bf::directory_entry> vdir) {
  for (auto& filename : vdir) cout << filename << endl;
}
