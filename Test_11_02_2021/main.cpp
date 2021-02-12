#include <boost/program_options.hpp>

#include "parsingfiles.h"
namespace po = boost::program_options;
int main(int argc, char* argv[]) {
  //    argv[1] - путь к директории (по умолчанию ./)
  //    argv[2] - путь к файлу с результатом  (по умолчанию ./results)
  po::options_description opt("All options");

  opt.add_options()("path_dir", po::value<std::string>(), "path to directory")(
      "path_out_file", po::value<std::string>(), "path to result file");

  po::variables_map vm;  // Variable to store our command line arguments.
                         // Let's parse config file:
  try {
    po::store(po::parse_config_file<char>("../parsing_config.ini", opt), vm);
  } catch (const po::reading_file& e) {
    std::cout << "Error: " << e.what() << std::endl;
    return 2;
  }

  po::notify(vm);  // Must be called after all the parsing and storing.

  std::cout << vm["path_dir"].as<std::string>() << std::endl;
  std::cout << vm["path_out_file"].as<std::string>() << std::endl;

  //корректная обработка неправильной директории
  //корректная обработка argv
  ParsingFiles p;
  p.ParsingDir(vm["path_dir"].as<std::string>());
}
