//  quick-delete.cpp by Bill Weinman [bw.org]
//  as of 2026-05-04

#include <print>
#include <vector>
#include <algorithm>

using std::print, std::println;
using std::vector;
using std::move;
using std::ranges::find;

void printc(const auto & r) {
    print("size({}) ", r.size());
    for (auto & e : r) print("{} ", e);
    print("\n");
}

template<typename T>
void quick_delete(T& v, const std::size_t idx) {
    if (idx < v.size() - 1) {
        if (idx != v.size() - 1) {
            v[idx] = std::move(v.back());
        }
        v.pop_back();
    }
}

template<typename T>
void quick_delete(T& v, typename T::iterator it) {
    if (it != v.end()) {
        if (it != std::prev(v.end())) {
            *it = std::move(v.back());
        }
        v.pop_back();
    }
}

int main() {
    vector v {12, 196, 47, 38, 19};
    printc(v);
    auto it = find(v, 47);
    quick_delete(v, it);
    printc(v);
    quick_delete(v, 1);
    printc(v);
}
