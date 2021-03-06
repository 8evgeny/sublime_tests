#include <vector>

typedef std::vector<int> veci;

using vi = std::vector<int>;

template<typename T>
using v = std::vector<T>;

int main(int, char *[]) {
    vi a;
    v<int> b;

    return 0;
}
