#include <fstream>
#include <vector>
using namespace std;
#include "main.h"
//Создание строки для парсинга из текстового файла. Файл - первый параметр, путь
//к строке - второй.
int main(int argc, char** argv) {
  if (argc != 3) {
    cout << "Expected parametr" << endl;
    exit(1);
  }

  fstream in(argv[1], ios::in | ios::binary);
  char c;
  vector<char> v;
  while (!in.eof()) {
    c = in.get();
    if ((c != ' ') && (c != '\n')) v.push_back(c);
  }
  fstream out(argv[2], ios::out | ios::binary);
  for (auto& x : v) {
    out << x;
  }
  return 0;
}
