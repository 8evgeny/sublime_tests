#include <boost/program_options.hpp>
#include <iostream>
namespace opt = boost::program_options;

//аргументы запуска --apples 10  --oranges 20(или --o 20)  либо --help
int main(int argc, char *argv[])
{
// Constructing an options describing variable and giving it a textual description "All options".
opt::options_description desc("All options");

// When we are adding options, first parameter is a name to be used in command line.
//Second parameter is a type of that option, wrapped in value<> class. Third parameter
// must be a short description of that option.

int oranges_var = 0;
desc.add_options()
//("apples", opt::value<int>(), "how many apples do you have") //простая форма

// 'a' is a short option name for apples. Use as '-a 10'.
// If no value provided, then the default value is used.
("apples,a", opt::value<int>()->default_value(10), "apples that you have");

//("oranges", opt::value<int>(), "how many oranges do you have") //простая форма

// ProgramOptions stores the option value into the variable that is passed by pointer.
//Here value of "--oranges" option will be stored into 'oranges_var'.

("oranges,o", opt::value<int>(&oranges_var)->required(), "oranges you have") ("help", "produce help message")

// 'name' option is not marked with 'required()', so user may not provide it.
("name", opt::value<std::string>(), "your name");




// Let's parse the command line:
 opt::variables_map vm; // Variable to store our command line arguments.
 opt::store(opt::parse_command_line(argc, argv, desc), vm); // Parsing and storing arguments.
 std::cout << oranges_var << "\n"; //0
 opt::notify(vm);  // Must be called after all the parsing and storing.

 std::cout << oranges_var << "\n"; //20
 if (vm.count("help")) {
 std::cout << desc << "\n";
 return 1;
 }

 std::cout << "Fruits count: " << vm["apples"].as<int>() + vm["oranges"].as<int>() << std::endl;
 } // end of `main`

//vm["name"].as<std::string>()<<

