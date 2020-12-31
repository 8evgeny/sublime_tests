#include <iostream>
#include <vector>

template<class Iterator, class Sentinel=Iterator>
struct range_t {
Iterator b;
Sentinel e;
Iterator begin() const { return b; }
Sentinel end() const { return e; }
bool empty() const { return begin()==end(); }
range_t without_front( std::size_t count=1 ) const {
if (std::is_same< std::random_access_iterator_tag, typename
std::iterator_traits<Iterator>::iterator_category >{} ) {
count = (std::min)(std::size_t(std::distance(b,e)), count);
}
return {std::next(b, count), e};
}
range_t without_back( std::size_t count=1 ) const {
if (std::is_same< std::random_access_iterator_tag, typename
std::iterator_traits<Iterator>::iterator_category >{} ) {
count = (std::min)(std::size_t(std::distance(b,e)), count);
}
return {b, std::prev(e, count)};
}
};
template<class Iterator, class Sentinel>
range_t<Iterator, Sentinel> range( Iterator b, Sentinal e ) {
return {b,e};
}
template<class Iterable>
auto range( Iterable& r ) {
using std::begin; using std::end;
return range(begin(r),end(r));
}
template<class C>
auto except_first( C& c ) {
auto r = range(c);
if (r.empty()) return r;
return r.without_front();
}

// now we can do:

int main(){
std::vector<int> v = {1,2,3,4};
for (auto i : except_first(v))
std::cout << i << '\n';
}