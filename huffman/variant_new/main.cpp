#include <boost/program_options.hpp>
#include <iostream>
namespace po = boost::program_options;

int main() {
  // Constructing an options describing variable and giving it a textual
  // description "All options".
  po::options_description desc("All options");
  desc.add_options()("input_file,in", po::value<std::string>(), "input file")(
      "output_path,out", po::value<std::string>(), "output path");

  po::variables_map vm;  // Variable to store our command line arguments.

  // Let's parse config file:
  try {
    po::store(po::parse_config_file<char>("../../config.ini", desc), vm);
  } catch (const po::reading_file& e) {
    std::cout << "Error: " << e.what() << std::endl;
    return 2;
  }

  po::notify(vm);  // Must be called after all the parsing and storing.

  std::cout << vm["input_file"].as<std::string>() << std::endl;
  std::cout << vm["output_path"].as<std::string>() << std::endl;

  return 0;
}
