#include <vector>
#include <iostream>
#include <iomanip>
#include <iterator>
#include <algorithm>
// #include <ostream>

int main(){
std::cout << std::setprecision(3);
std::fixed(std::cout);

std::vector<int> v = {1, 2, 3, 4, 8, 42};
std::copy(v.begin(), v.end(), std::ostream_iterator<float>(std::cout, " ! "));
std::cout <<'\n';

std::vector<int> v1 = {1,2,3,4,8,16};
std::boolalpha(std::cout); // print booleans alphabetically

std::transform(v1.begin(), v1.end(), std::ostream_iterator<bool>(std::cout, " "),
[](int val) {
return (val % 2) == 0;
});
std::cout <<'\n';

std::transform(v1.begin(), v1.end(), std::ostream_iterator<int>(std::cout, " "),
[](int val) {
return val * val;
});
std::cout <<'\n';

const int N = 20;
std::generate_n(std::ostream_iterator<int>(std::cout, " "), N, std::rand);
std::cout <<'\n';

int v2[] = {1,2,3,4,8,16};
std::transform(v2, std::end(v2), std::ostream_iterator<int>(std::cout, " "),
[](int val) {
return val * val * val;
});
std::cout <<'\n';



}
