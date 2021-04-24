#include <boost/signals2.hpp>
#include <iostream>
using namespace boost::signals2;

float product(float x, float y) { return x * y; }
float quotient(float x, float y) { return x / y; }
float sum(float x, float y) { return x + y; }
float difference(float x, float y) { return x - y; }

// aggregate_values is a combiner which places all the values returned
// from slots into a container
template<typename Container>
struct aggregate_values
{
    typedef Container result_type;

    template<typename InputIterator>
    Container operator()(InputIterator first, InputIterator last) const
    {
        Container values;

        while(first != last) {
            values.push_back(*first);
            ++first;
        }
        return values;
    }
};

int main() {
    boost::signals2::signal<float (float, float),
                            aggregate_values<std::vector<float> > > sig;
    sig.connect(&quotient);
    sig.connect(&product);
    sig.connect(&sum);
    sig.connect(&difference);

    std::vector<float> results = sig(5, 3);
    std::cout << "aggregate values: ";
    std::copy(results.begin(), results.end(),
              std::ostream_iterator<float>(std::cout, " "));
    std::cout << "\n";
}
