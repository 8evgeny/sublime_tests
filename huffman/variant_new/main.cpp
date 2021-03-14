#include "main.h"

int main(int argc, char** argv) {
  if (argc == 2) {
    switch (*argv[1]) {
      case 'c': {
        cout << "Codding file" << endl;
        Coding coding;
        break;
      }
      case 'd': {
        cout << "Decodding file" << endl;
        Decoding decoding;
        break;
      }
      default:
        cout << "invalid argument!" << endl;
        break;
    }
  } else
  // если аргументов нет сначала содируем а потом декодируем
  {
    Coding coding;
  }
  cout << "wait 1 seconds" << endl;
  this_thread::sleep_for(chrono::milliseconds(1000));
  { Decoding decoding; }
  return 0;
}
