#include <eth_ttl.hpp>
#include <iostream>
#include <thread>

using namespace std;

int main(int argc, char *argv[])
{
    unique_ptr<eth_ttl> p = make_unique<eth_ttl>();
    p->send_udp();

return 0;
}// END while(1)



