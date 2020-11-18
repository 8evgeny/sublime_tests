#include <boost/program_options.hpp>
#include <iostream>
namespace po = boost::program_options;

int main(int argc, char *argv[])
{
// Constructing an options describing variable and giving it a textual description "All options".
po::options_description desc("All options");

int oranges_var = 0;
desc.add_options()
("apples,a", po::value<int>(), "apples that you have")
("name", po::value<std::string>(), "your name")
("oranges", po::value<int>(), "how many oranges do you have");

po::variables_map vm ; // Variable to store our command line arguments.

// Let's parse config file:
 try {
 po::store(
 po::parse_config_file<char>("apples_oranges.ini", desc),
 vm
 );
 } catch (const po::reading_file& e) {
 std::cout << "Error: " << e.what() << std::endl;
 return 2;
 }

 po::notify(vm);  // Must be called after all the parsing and storing.

 std::cout <<vm["name"].as<std::string>()<< std::endl;
 std::cout << "Fruits count: " << vm["apples"].as<int>() + vm["oranges"].as<int>() << std::endl;
 } // end of `main`



