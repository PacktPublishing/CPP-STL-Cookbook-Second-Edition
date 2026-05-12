//  algorithm.cpp by Bill Weinman [bw.org]
//  as of 2026-05-11

#include <print>
#include <string>
#include <vector>
#include <algorithm>

using std::print, std::println;
using std::string;
using std::vector;
using std::count_if;

namespace ranges = std::ranges;

auto is_div_by(const int& divisor) {
    return [&divisor] (int i) { return i % divisor == 0; };
}

int main() {
    vector<int> v {1, 7, 12, 20, 4, 9, 4, 8};
    
    auto is_div4 = [](int i){ return i % 4 == 0; };
    auto count4 = count_if(v.begin(), v.end(), is_div4);
    println("numbers divisible by 4 (is_div4): {}", count4);

    for (int i : {3, 4, 5}) {
        auto pred = is_div_by(i);
        auto count = count_if(v.begin(), v.end(), pred);
        println("numbers divisible by {}: {} (is_div_by)", i, count);
    }

    auto comp = [](int a, int b) { return a > b; };
    println("unsorted: {}", v);
    ranges::sort(v, comp);
    println("sorted: {}", v);
}
