// createSpan.cpp

#include <algorithm>
#include <iostream>
#include <span>
#include <vector>
template<class T>
void print(T cont){
    for (auto &i:cont)
        std::cout<<i<<" ";
    std::cout<<"\n";
}
int main() {

    std::cout << '\n';
    std::cout << std::boolalpha;

std::vector myVec{1, 2, 3, 4, 5};
print(myVec);

    std::span mySpan1{myVec};
print(mySpan1);

    std::span mySpan2{myVec.data(), myVec.size()};
//    std::span mySpan2{myVec.data(), 3};
print(mySpan2);


    bool spansEqual = std::equal(mySpan1.begin(), mySpan1.end(),
                                 mySpan2.begin(), mySpan2.end());
	
    std::cout << "mySpan1 == mySpan2: " << spansEqual << '\n';  

    std::cout << '\n';
	
}
