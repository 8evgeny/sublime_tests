#include <boost/signals2.hpp>
#include <iostream>
using namespace boost::signals2;

float product(float x, float y) { return x * y; }
float quotient(float x, float y) { return x / y; }
float sum(float x, float y) { return x + y; }
float difference(float x, float y) { return x - y; }

// combiner which returns the maximum value returned by all slots
template <typename T>
struct maximum {
  typedef T result_type;

  template <typename InputIterator>
  T operator()(InputIterator first, InputIterator last) const {
    // If there are no slots to call, just return the
    // default-constructed value
    if (first == last) return T();
    T max_value = *first++;
    while (first != last) {
      if (max_value < *first) max_value = *first;
      ++first;
    }

    return max_value;
  }
};

int main() {
  boost::signals2::signal<float(float x, float y), maximum<float> > sig;
  sig.connect(&product);
  sig.connect(&quotient);
  sig.connect(&sum);
  sig.connect(&difference);

  // Outputs the maximum value returned by the connected slots, in this case
  // 15 from the product function.
  std::cout << "maximum: " << sig(5, 3) << std::endl;
}
