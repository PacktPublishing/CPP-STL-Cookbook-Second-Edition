//  word-count.cpp by Bill Weinman [bw.org]
//  as of 2026-05-06

#include <print>
#include <iostream>
#include <algorithm>
#include <map>
#include <vector>
#include <algorithm>
#include <utility>
#include <string>
#include <regex>
#include <cctype>

using std::println;
using std::cout;
using std::string;
using std::map;
using std::vector;
using std::pair;
using std::regex;
using std::sregex_iterator;
using std::smatch;
using std::cin;

namespace ranges = std::ranges;
namespace regex_constants = std::regex_constants;

namespace bw {
    constexpr const char * re {"(\\w+)"};
}

int main() {
    map<string, int> wordmap {};
    vector<pair<string, int>> wordvec {};
    regex word_re(bw::re);
    size_t total_words {};

    for (string s {}; cin >> s; ) {
        auto words_begin {sregex_iterator(s.begin(), s.end(), word_re)};
        auto words_end {sregex_iterator()};

        for (auto r_it {words_begin}; r_it != words_end; ++r_it) {
            smatch match {*r_it};
            auto word_str {match.str()};

            ranges::transform(word_str, word_str.begin(),
                [](unsigned char c){ return tolower(c); });

            auto [map_it, result] = wordmap.try_emplace(word_str, 0);
            auto & [w, count] = *map_it;
            ++total_words;
            ++count;
        }
    }

    auto unique_words = wordmap.size();
    wordvec.reserve(unique_words);
    ranges::move(wordmap, back_inserter(wordvec));
    ranges::sort(wordvec, [](const auto& a, const auto& b) { 
        if (a.second != b.second)
            return (a.second > b.second);
        return (a.first < b.first);
    });

    println("total word count: {}", total_words);
    println("unique word count: {}", unique_words);

    for (int limit {20}; auto& [w, count] : wordvec) {
        println("{}: {}", count, w);
        if (--limit == 0) break;
    }
}
