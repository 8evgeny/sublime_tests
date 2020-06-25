#include <iostream>
#include <deque>
#include <list>
#include <vector>
#include <functional>

template<class A>  //замена auto - предупреждение выдает
static auto consumer (A & container) {
	return [&] (auto value) {container.push_back(value);};
}
template<class B>
static void print (const B & c)
{
	for (auto i : c) {
		std::cout << i << ", ";
	}
	std::cout << '\n';
}
int main() {
	std::deque<int> d;
	std::list<int> l;
	std::vector<int> v;

	const std::vector<std::function<void(int)>> consumers
	{consumer(d), consumer(l), consumer(v)};
	for (size_t i {0}; i < 10; ++i) {
		for (auto && consume : consumers) {
			consume(i);
		}
	}

	print(d);
	print(l);
	print(v);




}
