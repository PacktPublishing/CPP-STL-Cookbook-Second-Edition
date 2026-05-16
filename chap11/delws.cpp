// delws.cpp by Bill Weinman [bw.org]
// as of 2026-05-16

#include <print>
#include <iostream>
#include <string>
#include <algorithm>

using std::print, std::println;
using std::string;

namespace bw {
    using std::unique;

    template<typename T>
    bool isws(const T& c) {
        constexpr const T whitespace[] {" \t\r\n\v\f"};
        for (const T& wsc : whitespace) if (c == wsc) return true;
        return false;
    }

    string delws(const string& s) {
        string outstr {s};
        auto its = unique(outstr.begin(), outstr.end(),
            [](const auto &a, const auto &b) {
                return isws(a) && isws(b);
            });
        outstr.erase(its, outstr.end());
        outstr.shrink_to_fit();
        return outstr;
    }
};

int main() {
    const string s {"big     bad    \t   wolf"};
    const string s2 {bw::delws(s)};
    println("[{}]", s);
    println("[{}]", s2);
    return 0;
}
