// regex.cpp bw [bw.org]
// as of 2026-05-13

#include <print>
#include <string>
#include <iostream>
#include <fstream>
#include <iterator>
#include <regex>
#include <iomanip>

using std::println;
using std::cin;
using std::string;

template<typename It>
void get_links(It it) {
    for (It end_it{}; it != end_it; ) {
        const string link {*it++};
        if (it == end_it) break;
        const string desc {*it++};

        println("{:.<24} {}", desc, link);
    }
}

int main() {
    const char * fn {"the-end.html"};
    const std::regex link_re {"<a href=\"([^\"]*)\"[^<]*>([^<]*)</a>"};

    string in {};
    std::ifstream infile(fn, std::ios_base::in);
    for (string line {}; getline(infile, line);) in += line;

    std::sregex_token_iterator it {in.begin(), in.end(), link_re, {1, 2}};
    get_links(it);
}
