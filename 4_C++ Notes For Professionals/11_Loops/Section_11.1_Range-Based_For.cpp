#include <vector>
#include <iostream>

int main(){
std::vector<float> v = {0.4f, 12.5f, 16.234f};
for(auto val: v)
{
std::cout << val << " ";
}
std::cout << std::endl;

//is equivalent to:
//for (for-range-declaration : for-range-initializer ) statement

// auto&& __range = for-range-initializer;
// auto __begin = begin-expr, __end = end-expr;
// for (; __begin != __end; ++__begin) {
// for-range-declaration = *__begin;
// statement

auto&& __range = v;
auto __begin = v.begin(), __end = v.end();
for (; __begin != __end; ++__begin) {
auto val = *__begin;
std::cout << val << " ";
}
std::cout << std::endl;

std::vector<float> v1 = {0.4f, 12.5f, 16.234f};
for(float &val: v1)
{
std::cout << val << " ";
}
std::cout << std::endl;

const std::vector<float> v2 = {0.4f, 12.5f, 16.234f};
for(const float &val: v2)
{
std::cout << val << " ";
}
std::cout << std::endl;

std::vector<bool> v3(10);
for(auto&& val: v3)
{
val = true;
}

float arr[] = {0.4f, 12.5f, 16.234f};
for(auto val: arr)
{
std::cout << val << " ";
}
std::cout << std::endl;

// Note that allocating a dynamic array does not count:
// float *arr = new float[3]{0.4f, 12.5f, 16.234f};
// for(auto val: arr) //Compile error.
// {
// std::cout << val << " ";





}