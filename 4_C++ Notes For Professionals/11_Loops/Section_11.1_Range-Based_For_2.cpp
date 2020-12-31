#include <iostream>
namespace Mine
{
	struct Rng
	{
	float arr[3];
	// pointers are iterators
	const float* begin() const {return &arr[0];}
	const float* end() const
	 {return &arr[3];}
	float* begin() {return &arr[0];}
	float* end()
	 {return &arr[3];}
	};
}

int main()
{
	Mine::Rng rng = {{0.4f, 12.5f, 16.234f}};
	for(auto val: rng)
	{
	std::cout << val << " ";
}




}
