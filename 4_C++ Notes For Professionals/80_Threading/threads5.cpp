#include <iostream>
#include <thread>
using namespace std;
// Passing a reference to a thread

class ComplexObject {
 public:
  ComplexObject(){};
  void getResult() const { cout << aa << endl; }
  void doCalculations() const { cout << "doCalculations" << endl; }
  int aa = 3;
};

void foo(int& b) { b = 10; }

void bar(const ComplexObject& co) { co.doCalculations(); }

int main() {
  int a = 1;
  std::thread thread{foo, std::ref(a)};  //'a' is now really passed as reference
  thread.join();
  std::cout << a << '\n';  // Outputs 10

  ComplexObject object;
  std::thread thread2{bar, std::cref(object)};  //'object' is passed as const&
  thread2.join();
  object.getResult() ;  // Outputs the result

  return 0;
}
