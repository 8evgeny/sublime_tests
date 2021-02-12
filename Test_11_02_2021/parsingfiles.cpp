#include "parsingfiles.h"
using namespace std;

struct ParsingFiles::Impl {
  Impl();

  std::vector<boost::filesystem::directory_entry> ReadDirImpl(std::string);
  void ReadFileImpl();
  std::vector<boost::filesystem::directory_entry> v;
  void PrintDir(std::vector<boost::filesystem::directory_entry> v);
};

ParsingFiles::Impl::Impl() {}

ParsingFiles::ParsingFiles() : _d{std::make_unique<Impl>()} {}

ParsingFiles::~ParsingFiles() {}

void ParsingFiles::ParsingDir(std::string p) {
  std::vector<boost::filesystem::directory_entry> v = _d->ReadDirImpl(p);
  _d->PrintDir(v);
}

std::vector<boost::filesystem::directory_entry> ParsingFiles::Impl::ReadDirImpl(
    std::string pathdir) {
  boost::filesystem::directory_iterator p(pathdir);
  for (boost::filesystem::directory_entry& x :
       boost::filesystem::directory_iterator(p)) {
    boost::filesystem::file_status fs = x.status();
    if (fs.type() == boost::filesystem::regular_file) {
      v.push_back(x);
    }
  }
  return v;
}

void ParsingFiles::Impl::PrintDir(
    std::vector<boost::filesystem::directory_entry> v) {
  for (auto& x : v) cout << x << endl;
}
