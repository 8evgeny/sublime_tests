
#include "parsingfiles.h"

int main(int argc, char* argv[]) {
  //    argv[1] - путь к директории (по умолчанию ./)
  //    argv[2] - путь к файлу с результатом  (по умолчанию ./results)

  //корректная обработка неправильной директории
  //корректная обработка argv
  ParsingFiles p;
  p.ParsingDir(argv[1]);
}
