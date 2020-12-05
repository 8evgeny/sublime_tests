#include <cstddef>
#include <iostream>
#include <stdexcept>

template <typename T>
T get_value(T t) {
	if (std::is_pointer_v<T>) {
		std::cout << "get_value - pointer detected!" << std::endl;
        return *t;
	}
	else {
		std::cout << "get_value - value detected!" << std::endl;
        return t;
	}
}

template <typename T>
T get_value2(T t) {
	std::cout << "get_value2 - value detected!" << std::endl;
	return t;
}

template <typename T>
T get_value2(T* t) {
	std::cout << "get_value2 - pointer detected!" << std::endl;
	if (t == nullptr)
		throw std::logic_error("nullptr detected!");
	return *t;

}


template <typename T>
T get_value3(T t) {
    if constexpr (std::is_pointer_v<T>) {
    	std::cout << "get_value3 - pointer detected!" << std::endl;
        return t;
    }
    else {
    	std::cout << "get_value3 - value detected!" << std::endl;
        return t;
    }
}

int main() {
	int value = 42;

//	 get_value(value);
//	 get_value(&value);

//	get_value2(value);
//	get_value2(&value);

	get_value3(value);
	get_value3(&value);

	return 0;
}
