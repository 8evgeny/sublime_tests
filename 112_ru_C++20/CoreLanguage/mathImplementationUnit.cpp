// mathImplementationUnit.cpp

module math;

#include <numeric>

namespace math {

    int add(int fir, int sec) {
        return fir + sec;
    }

    int getProduct(const std::vector<int>& vec) {
        return std::accumulate(vec.begin(), vec.end(), 1, std::multiplies<int>());
    }

}