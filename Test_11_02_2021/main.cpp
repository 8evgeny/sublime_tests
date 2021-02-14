#include "main.h"

#include <thread>
int main(int argc, char** argv) {
  if (argc != 3) {
    std::cout << "Expected parametr" << std::endl;
    exit(1);
  }
  ParsingFiles parser;

  parser.ParsingDir(argv[1], argv[2]);

  return 0;
}
