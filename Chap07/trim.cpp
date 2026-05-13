// trim.cpp by Bill Weinman [bw.org]
// as of 2026-05-13

#include <print>
#include <string>

using std::println;
using std::string;

string trimstr(const string& s) {
    constexpr const char * whitespace {" \t\r\n\v\f"};

    if (s.empty()) return s;     // empty string
    const auto first = s.find_first_not_of(whitespace);
    if (first == string::npos) return {};  // all whitespace
    const auto last = s.find_last_not_of(whitespace);
    return s.substr(first, (last - first + 1));
}

int main() {
    string s {" \t  ten-thumbed input   \t   \n \t "};
    println("[{}]", s);
    s = trimstr(s);
    println("[{}]", s);
}
