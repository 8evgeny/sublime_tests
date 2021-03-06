// priority_queue
#include <iostream>
#include <queue>

int main()
{
    std::priority_queue<int> pq;
    for(auto i: {6, 7, 4, 8, 3, 8, 8})
    {
        pq.push(i);
    }

    while(!pq.empty())
    {
        std::cout << pq.top() << " ";
        pq.pop();
    }
    std::cout << std::endl;
}
