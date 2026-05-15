// optional.cpp by  [bw.org]
// as of 2026-05-14

#include <print>
#include <iostream>
#include <optional>

using std::print, std::println;
using std::optional;

using oint = std::optional<int>;
using olong = std::optional<long>;

oint operator+(const oint& a, const oint& b) {
    if (a && b) return *a + *b;
    return {};
}

oint operator+(const oint& a, const int b) {
    if (a) return *a + b;
    return {};
}

olong factor(const olong& n) {
    if (!n) return {};
    for (long i = 2; i <= *n / 2; ++i) {
        if (*n % i == 0) return {i};
    }
    return {};
}

int main() {
    oint a {42};
    oint b {73};

    auto sum {a + b};

    if (sum) {
        println("{} + {} = {}", *a, *b, *sum);
    } else {
        println("no value");
    }

    auto x = factor(a);
    auto y = factor(b);
    if (x) println("lowest factor of {} is {}", *a, *x);
    else println("{} has no factor", *a);
    if (y) println("lowest factor of {} is {}", *b, *y);
    else println("{} has no factor", *b);

    b.reset();
    try {
        println("{}", b.value());
    } catch(const std::bad_optional_access& e) {
        println("b.value(): {}", e.what());
    }
}
