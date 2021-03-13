#include "main.h"

int main(int argc, char** argv) {
  if (argc == 2) {
    switch (*argv[1]) {
      case 'c': {
        cout << "Codding file" << endl;
        Codding codding;
        break;
      }
      case 'd': {
        cout << "Decodding file" << endl;
        //      Decodding decodding;
        break;
      }
      default:
        cout << "invalid argument!" << endl;
        break;
    }
  } else
    cout << "no argument!" << endl;
  return 0;
}
