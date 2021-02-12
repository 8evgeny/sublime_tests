#include "parsingfiles.h"
using namespace std;
namespace bf = boost::filesystem;

#include <boost/lexical_cast.hpp>

struct ParsingFiles::Impl {
  Impl();

  std::vector<bf::directory_entry> ReadDir(std::string);
  void PrintDir(std::vector<bf::directory_entry> v);
  void ReadFile();

  std::vector<bf::directory_entry> v;
  std::vector<std::string> vv;
};  // namespace boost::filesystemstructParsingFiles::Impl

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
      vv.push_back(boost::lexical_cast<std::string>(x));
    }
  }
  return v;
}

void ParsingFiles::Impl::PrintDir(std::vector<bf::directory_entry> vdir) {
  for (auto& filename : vdir) cout << filename << endl;
}
