// print.cpp by Bill Weinman [bw.org]
// as of 2026-05-13

#include <print>
#include <fstream>

using std::print, std::println;

template<typename T>
struct Frac {
    T n;
    T d;
};

template <typename T>
struct std::formatter<Frac<T>>: std::formatter<int> {
    template<typename FormatContext>
    auto format(const Frac<T>& o, FormatContext& ctx) const {
        return format_to(ctx.out(), "{}/{}", o.n, o.d);
    }
};

int main() {
    const char* greeting {"earthlings"};
    print("hello, {}!\n", greeting);

    print("one");
    print("two");
    print("three");
    print("\n");
    println("one");
    println("two");
    println("three");

    // this C++23 feature may not yet be implemented
    const char* filename {"output.txt"};
    std::ofstream ofile(filename);
    if (ofile.is_open()) {
        println("Writing to {}", filename);
        println(ofile, "hello, {}!", greeting);
        ofile.close();
        println("done.");
    } else {
        println(stderr, "failed to open file {}", filename);
    }

    Frac<int> f {5, 3};
    println("Frac f {{5, 3}}: {}", f);
}
