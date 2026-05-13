//  transform.cpp by Bill Weinman [bw.org]
//  as of 2026-05-13

#include <print>
#include <string>
#include <algorithm>

using std::print, std::println;
using std::string;
using std::string_view;

namespace ranges = std::ranges;

const char char_upper(const char c) {
    if (c >= 'a' && c <= 'z') return c - ('a' - 'A');
    else return c;
};

const char char_lower(const char c) {
    if (c >= 'A' && c <= 'Z') return c + ('a' - 'A');
    else return c;
};

const char rot13(const char& x) {
    auto rot13c = [](const char x, const char a) -> const char {
        return a + (x - a + 13) % 26;
    };
    if (x >= 'A' && x <= 'Z') return rot13c(x, 'A');
    if (x >= 'a' && x <= 'z') return rot13c(x, 'a');
    return x;
}
 
const string& title_case(string& s) {
    auto begin = s.begin();
    auto end = s.end();
    *begin++ = char_upper(*begin);  // first element
    bool space_flag {false};
    for (auto it {begin}; it != end; ++it) {
        if (*it == ' ') {
            space_flag = true;
        } else {
            if (space_flag) *it = char_upper(*it);
            space_flag = false;
        }
    }
    return s;
}

int main() {
    string s {"hello jimi"};
    println("{}", s);

    ranges::transform(s, s.begin(), char_upper);
    println("{}", s);

    for (auto& c : s) c = rot13(c);
    println("{}", s);

    for (auto& c : s) c = rot13(char_lower(c));
    println("{}", s);

    println("{}", title_case(s));
}
