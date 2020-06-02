#include <iostream>
#include <functional>

// template <typename T, typename ...Ts>
// auto concat(T t, Ts ...ts) {
// 	if constexpr (sizeof...(ts) > 0) {
// 		return [ = ](auto ...parameters) {
// 			return t(concat(ts...)(parameters...));
// 		};
// 	}
// 	else {
// 		return t;
// 	}
// }

//Напишем более простую версию этой функции, которая объединяет ровно три функции:

template <typename F, typename G, typename H>
auto concat(F f, G g, H h)
{
	return [ = ](auto ... params) {
		return f( g( h( params... ) ) );
	};
}

int main() {

	auto twice ([] (int i) { return i * 2; });
	auto thrice ([] (int i) { return i * 3; });

	auto combined (
	    concat(twice, thrice, std::plus<int> {})
	);
	std::cout << combined(2, 3) << '\n';

}
