#include "main.h"
using namespace std;

struct Decoding::Impl {
  Impl();
  void readConfig(const char*);
  po::variables_map config;
};

Decoding::Impl::Impl() {}

Decoding::Decoding() : _d{make_unique<Impl>()} {
  cout << "Decodding_constructor" << endl;
  _d->readConfig("../../config.ini");
  //    _d->decodding();
  //    _d->writeFile();
}
Decoding::~Decoding() {}

void Decoding::Impl::readConfig(const char* conf_file) {
  po::options_description decoding("decoding");
  decoding.add_options()("decoding.input_path_decodding,in",
                         po::value<std::string>(), "input_path")(
      "decoding.output_path_decodding,out", po::value<std::string>(),
      "output path decoding")("decoding.name_input_decodding,iname",
                              po::value<std::string>(), "name_input coding")(
      "decoding.name_output_decodding,oname", po::value<std::string>(),
      "name_output decoding");
  po::options_description desc("Allowed options");
  desc.add(decoding);
  try {
    po::parsed_options parsed = po::parse_config_file<char>(
        conf_file, desc,
        true);  //флаг true разрешает незарегистрированные опции !
    po::store(parsed, config);
  } catch (const po::reading_file& e) {
    std::cout << "Error: " << e.what() << std::endl;
  }
  po::notify(config);
  std::cout << config["decoding.input_path_decodding"].as<std::string>()
            << std::endl;
  std::cout << config["decoding.name_input_decodding"].as<std::string>()
            << std::endl;
  std::cout << config["decoding.output_path_decodding"].as<std::string>()
            << std::endl;
  std::cout << config["decoding.name_output_decodding"].as<std::string>()
            << std::endl;
}
