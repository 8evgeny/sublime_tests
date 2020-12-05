// queue
#include <iostream>
#include <queue>

int main()
{
    // первый добавленный и извлекается первым
    // FIFO
    std::queue<int> q;
    for(auto i: {6, 7, 4, 8, 3, 8, 8})
    {
        q.push(i);
    }

    while(!q.empty())
    {
        std::cout << q.front() << " ";
        q.pop();
    }
    std::cout << std::endl;
}
