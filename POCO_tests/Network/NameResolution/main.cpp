#include "Poco/Net/DNS.h"
#include <iostream>

using Poco::Net::DNS;
using Poco::Net::IPAddress;
using Poco::Net::HostEntry;

int main(int argc, char** argv)
{
    const HostEntry& entry = DNS::hostByName("www.google.com");
    std::cout << "Canonical Name: " << entry.name() << std::endl;
    const HostEntry::AliasList& aliases = entry.aliases();
    HostEntry::AliasList::const_iterator it = aliases.begin();
    for (; it != aliases.end(); ++it)
    std::cout << "Alias: " << *it << std::endl;
    const HostEntry::AddressList& addrs = entry.addresses();
    HostEntry::AddressList::const_iterator it1 = addrs.begin();
    for (; it1 != addrs.end(); ++it1)
    std::cout << "Address: " << it1->toString() << std::endl;
    return 0;
}
