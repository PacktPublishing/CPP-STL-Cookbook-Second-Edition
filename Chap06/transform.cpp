// transform.cpp by Bill Weinman [bw.org]
// as of 2026-05-12

#include <print>
#include <string>
#include <string_view>
#include <vector>
#include <cctype>
#include <algorithm>
#include <iterator>
#include <ranges>

using std::print, std::println;
using std::string;
using std::string_view;
using std::vector;
using std::transform;
using std::back_inserter;

namespace ranges = std::ranges;
namespace views = ranges::views;

void printc(auto& c, string_view s = "") {
    if (s.size()) print("{}: ", s);
    for (const auto& e : c) print("{} ", e);
    print("\n");
}

// return a lowercase version of string s — ascii only
string str_lower(string s) {
    auto char_lower = [](char c) -> char {
        if(c >= 'A' && c <= 'Z') return c + ('a' - 'A');
        else return c;
    };
    for (auto& c : s) c = char_lower(c);
    return s;
}

int main() {
    vector<int> v1 {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    vector<int> v2 {};
    printc(v1, "v1");

    println("squares:");
    transform(v1.begin(), v1.end(), back_inserter(v2), [](int x) { return x * x; });
    printc(v2, "v2");

    vector<string> vstr1 {"Mercury", "Venus", "Earth", "Mars",
        "Jupiter", "Saturn", "Uranus", "Neptune", "Pluto"};
    vector<string> vstr2 {};

    printc(vstr1, "vstr1");
    println("str_lower:");
    transform(vstr1.begin(), vstr1.end(), back_inserter(vstr2), [](string& x) { return str_lower(x); });
    printc(vstr2, "vstr2");

    println("ranges squares:");
    auto view1 = views::transform(v1, [](int x) { return x * x; });
    printc(view1, "view1");

    v2.clear();
    for (auto e : v1) v2.push_back(e * e);
    printc(v2, "v2");
}
