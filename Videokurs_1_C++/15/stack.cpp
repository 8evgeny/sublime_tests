// stack
#include <iostream>
#include <stack>

int main()
{
    // последний добавленный извлекается первым
    // LIFO
    std::stack<int> s;
    for(auto i: {6, 7, 4, 8, 3, 8, 8})
    {
        s.push(i);
    }

    while(!s.empty())
    {
        std::cout << s.top() << " ";
        s.pop();
    }
    std::cout << std::endl;
}
