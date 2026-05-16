// numword-test.cpp by Bill Weinman [bw.org]
// updated 2022-03-24

#include <print>
#include <string>
#include "numword.h"

using std::println;

template<>
struct std::formatter<bw::numword>: std::formatter<std::string> {
    template<typename FormatContext>
    auto format(const bw::numword& nw, FormatContext& ctx) const {
        bw::numword _nw{nw};
        return std::formatter<std::string, char>::format(_nw.words(), ctx);
    }
};

int main() {
    bw::numword nw {};
    bw::numnum n {};

    println("n is {}, {}", nw.getnum(), nw);

    nw = 3; println("n is {}, {}", nw.getnum(), nw);
    nw = 47; println("n is {}, {}", nw.getnum(), nw);
    nw = 73; println("n is {}, {}", nw.getnum(), nw);
    nw = 1492; println("n is {}, {}", nw.getnum(), nw);
    nw = 10012; println("n is {}, {}", nw.getnum(), nw);
    
    n = 100073; println("n is {}, {}", n, bw::numword{n});
    n = 1000000; println("n is {}, {}", n, bw::numword{n});
    n = 1000000001; println("n is {}, {}", n, bw::numword{n});
    n = 123000000000; println("n is {}, {}", n, bw::numword{n});

    n = 474142398123; println("n is {}, {}", n, nw(n));
    n = 1474142398007; println("n is {}, {}", n, nw(n));
    n = 999000000000000; println("n is {}, {}", n, nw(n));
    n = 999999999999999999; println("n is {}, {}", n, nw(n));
    n = 1000000000000000000; println("n is {}, {}", n, nw(n));
}
