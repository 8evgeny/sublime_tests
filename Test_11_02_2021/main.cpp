#include <boost/program_options.hpp>

#include "parsingfiles.h"
namespace po = boost::program_options;
int main() {
  po::options_description opt("All options");

  opt.add_options()("path_dir", po::value<std::string>(), "dir")(
      "path_out_file", po::value<std::string>(), "out");

  po::variables_map vm;
  try {
    po::store(po::parse_config_file<char>("../parsing_config.ini", opt), vm);
  } catch (const po::reading_file& e) {
    std::cout << "Error: " << e.what() << std::endl;
    return 2;
  }
  po::notify(vm);
  std::cout << "Директория с файлами: " << vm["path_dir"].as<std::string>()
            << std::endl
            << std::endl;
  std::cout << "Результаты будут помещены в файл: "
            << vm["path_out_file"].as<std::string>() << std::endl
            << std::endl;
  ParsingFiles parser;
  parser.ParsingDir(vm["path_dir"].as<std::string>(),
                    vm["path_out_file"].as<std::string>());
}
