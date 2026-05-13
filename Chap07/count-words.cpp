// count-words.cpp by Bill Weinman [bw.org]
// as of 2026-05-13

#include <print>
#include <iostream>
#include <fstream>
#include <iterator>
#include <string>

using std::println;
using std::string;

size_t wordcount(auto& is) {
    using it_t = std::istream_iterator<string>;
    return std::distance(it_t(is), it_t());
}

int main() {
    auto fn = "the-raven.txt";
    auto infile = std::ifstream(fn, std::ios_base::in);
    println("There are {} words in the file.", wordcount(infile));
}
