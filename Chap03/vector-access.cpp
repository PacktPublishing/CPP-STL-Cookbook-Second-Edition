//  vector-access.cpp by Bill Weinman [bw.org]
//  as of 2026-05-07

#include <print>
#include <vector>

using std::println;
using std::vector;

int main() {
    vector v {19, 71, 47, 192, 4004};
    try {
        v.at(5) = 2001;
    } catch (const std::out_of_range & e) {
        println("Ouch!\n{}", e.what());
    }
    println("end element is {}", v.back());
}
