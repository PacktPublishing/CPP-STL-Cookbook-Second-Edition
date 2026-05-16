// split.cpp by Bill Weinman [bw.org]
// as of 2025-05-16

#include <print>
#include <string>
#include <iterator>
#include <vector>
#include <concepts>

#include <list>
#include <forward_list>

using std::print, std::println, std::format;
using std::string;
using std::vector;

template<typename Oc>
concept PushBackContainer =
    requires(Oc c, typename Oc::value_type v) {
        c.push_back(v);
    };

namespace bw {

    template<typename It, PushBackContainer Oc, typename V, typename Pred>
    It split(It it, const It end_it, Oc& dest, const V& sep, const Pred& f) {
        using SliceContainer = typename Oc::value_type;
        while (it != end_it) {
            SliceContainer dest_elm{};
            auto slice {it};
            while (slice != end_it) {
                if (f(*slice, sep)) break;
                dest_elm.push_back(*slice++);
            }
            dest.push_back(dest_elm);
            if (slice == end_it) return end_it;
            it = ++slice;
        }
        return it;
    }

    constexpr auto eq = [](const auto& el, const auto& sep) {
        return el == sep;
    };

    template<typename It, typename Oc, typename V>
    It split(It it, const It end_it, Oc& dest, const V& sep) {
        return split(it, end_it, dest, sep, eq);
    }

    template<typename Cin, typename Cout, typename V>
    Cout& strsplit(const Cin& str, Cout& dest, const V& sep) {
        split(str.begin(), str.end(), dest, sep, eq);
        return dest;
    }

};

int main() {
    constexpr char strsep {':'};
    const string str {"sync:x:4:65534:sync:/bin:/bin/sync"};
    vector<string> dest_vs{};

    bw::split(str.begin(), str.end(), dest_vs, strsep, bw::eq);
    for (const auto& e : dest_vs) print("[{}] ", e);
    print("\n");

    vector<string> dest_vs2 {};
    bw::strsplit(str, dest_vs2, strsep);
    for (const auto& e : dest_vs2) print("[{}] ", e);
    print("\n");

    constexpr int intsep {-1};
    vector<int> vi {1, 2, 3, 4, intsep, 5, 6, 7, 8, intsep, 9, 10, 11, 12};
    vector<vector<int>> dest_vi {};
    bw::split(vi.begin(), vi.end(), dest_vi, intsep);
    for (const auto& v : dest_vi) {
        string s {};
        for (const auto& e : v) s += format("{}", e);
        print("[{}] ", s);
    }
    print("\n");

    std::list<string> dest_ls2 {};
    bw::strsplit(str, dest_ls2, strsep);
    for (const auto& e : dest_ls2) print("[{}] ", e);
    print("\n");
}
