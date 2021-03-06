// Tokenizer

#include <boost/tokenizer.hpp>
#include <string>
#include <iostream>

int main() {
    std::string ip = "127.0.0.1:80";
    boost::tokenizer<boost::char_separator<char>>
            tokenizer{ip, boost::char_separator<char>{".:"}};

    for (auto i: tokenizer) {
        std::cout << i << std::endl;
    }
    std::cout << std::endl;

    // xml vs json vs csv vs ??? vs tsv

    std::string pack = "hello,real\\,world";
    boost::tokenizer<boost::escaped_list_separator<char>> escaped_tokenizer{pack};
    for (auto i : escaped_tokenizer) {
        std::cout << i << std::endl;
    }
}
