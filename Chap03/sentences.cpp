//  sentences.cpp by Bill Weinman [bw.org]
//  as of 2026-05-06

#include <print>
#include <iostream>
#include <string>
#include <string_view>
#include <vector>
#include <algorithm>
#include <cstring>
#include <memory>

using std::print;
using std::string;
using std::string_view;
using std::vector;
using std::ranges::sort;
using std::cin;
using std::unique_ptr;

constexpr const char * end_punct {".!?"};

int main() {
    vector<vector<string>> vv_sentences(1);

    for (string s {}; cin >> s; ) {
        vv_sentences.back().emplace_back(s);

        if (s.find_first_of(end_punct) != s.npos) {
            vv_sentences.emplace_back();
        }
    }

for (string s{}; cin >> s; ) {
    vv_sentences.back().emplace_back(s);

    if (s.find_first_of(end_punct) != s.npos) {
        vv_sentences.emplace_back();
    }
}

    // delete back if empty
    if (vv_sentences.back().empty()) vv_sentences.pop_back();

    sort(vv_sentences, [](const auto& l, const auto& r) {
            return l.size() > r.size();
        });

    for (const auto& v : vv_sentences) {
        constexpr auto WLIMIT = 10;
        size_t size = v.size();
        size_t limit {WLIMIT};
        print("{}: ", size);

        for (const auto& s : v) {
            print("{} ", s);
            if (--limit == 0) {
                if (size > WLIMIT) print("...");
                break;
            }
        }
        print("\n");

    }
    print("\n");
}
