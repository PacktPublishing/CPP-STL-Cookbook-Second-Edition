// gather.cpp by Bill Weinman [bw.org]
// as of 2026-05-16

#include <print>
#include <string>
#include <algorithm>
#include <functional>
#include <vector>

using std::print, std::println;
using std::string;
using std::vector;

namespace bw {
    using std::stable_partition;
    using std::pair;
    using std::not_fn;

    template <typename It, typename Pred>
    pair<It, It> gather(It first, It last, It pivot, Pred pred) {
        return {stable_partition(first, pivot, not_fn(pred)),
                 stable_partition(pivot, last, pred)};
    }

    // helper lambdas
    constexpr auto midit = [](auto& v) {
        return v.begin() + (v.end() - v.begin()) / 2;
    };

    constexpr auto is_even = [](auto i) {
        return i % 2 == 0;
    };

    constexpr auto is_even_char = [](auto c) {
        if(c >= '0' && c <= '9') return (c - '0') % 2 == 0;
        else return false;
    };
};

int main() {
    vector<int> vint {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
    string jenny {"867-5309"};

    auto gathered_even = bw::gather(vint.begin(), vint.end(), bw::midit(vint), bw::is_even);
    for (const auto& el : vint) print("{}", el);
    print("\n");

    auto& [it1, it2] = gathered_even;
    for (auto it {it1}; it < it2; ++it) print("{}", *it);
    print("\n");

    bw::gather(vint.begin(), vint.end(), vint.begin(), bw::is_even);
    for (const auto& el : vint) print("{}", el);
    print("\n");

    bw::gather(vint.begin(), vint.end(), vint.end(), bw::is_even);
    for (const auto& el : vint) print("{}", el);
    print("\n");

    bw::gather(jenny.begin(), jenny.end(), jenny.end(), bw::is_even_char);
    for (const auto& el : jenny) print("{}", el);
    print("\n");
}
