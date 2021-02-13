#include <fstream>
#include <vector>

#include "parsingfiles.h"
using namespace std;
int main(int argc, char** argv) {
  if (argc != 2) {
    std::cout << "Expected parametr" << std::endl;
    exit(1);
  }
  string output_string{
      "dfdffetedtyey!!gduheidijookpqpsp22kkjjjjjjjjjjjjjjjjswwwwwwwwwwwwww<<>>"
      "wwwwwwwwwwwy c              yyyyyyy"};
  vector<string> separators{"!!", "<<>>"};
  std::ofstream out;
  out.open(argv[1]);
  if (out.is_open()) {
    out << output_string << std::endl;
  }
  for (auto& x : separators) out << x << std::endl;
  return 0;
}
