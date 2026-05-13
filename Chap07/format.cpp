// format.cpp by Bill Weinman [bw.org]
// as of 2026-05-13

#include <format>
#include <string>
#include <string_view>
#include <numbers>

using std::format;
using std::string;
using std::string_view;

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

template<typename... Args>
void print(const string_view fmt_str, Args&&... args) {
    auto fmt_args = std::make_format_args(args...);
    auto outstr = std::vformat(fmt_str, fmt_args);
    fputs(outstr.c_str(), stdout);
}

int main() {
    string who {"everyone"};
    int ival {42};
    double pi {std::numbers::pi};
    auto s1 = format("Hello, {}!", who); // Hello, everyone!
    auto s2 = format("Integer: {}", ival); // Integer: 42
    auto s3 = format("π: {}", pi); // π: 3.141592653589793
    auto s4 = format("Hello {} {}", ival, who); // Hello everyone 42
    auto s5 = format("Hello {1} {0}", ival, who); // Hello everyone 42
    auto s6 = format("Hola {0} {1}", ival, who);  // Hola 42 everyone
    auto s7 = format("{:.<10}", ival);  // 42........
    auto s8 = format("{:.>10}", ival);  // ........42
    auto s9 = format("{:.^10}", ival);  // ....42....
    auto s10 = format("π: {:.5}", pi);  // π: 3.1416

    for (auto s : {s1, s2, s3, s4, s5, s6, s7, s8, s9, s10}) {
        print("{}\n", s);
    }

    print("{0}{0}{0}\n", "=====");
    print("Hello, {}!\n", who); // Hello, everyone!
    print("Integer: {}\n", ival); // Integer: 42
    print("π: {}\n", pi); // π: 3.141592653589793
    print("Hello {} {}\n", ival, who); // Hello everyone 42
    print("Hello {1} {0}\n", ival, who); // Hello everyone 42
    print("Hola {0} {1}\n", ival, who);  // Hola 42 everyone
    print("{:.<10}\n", ival);  // 42........
    print("{:.>10}\n", ival);  // ........42
    print("{:.^10}\n", ival);  // ....42....
    print("π: {:.5}\n", pi);  // π: 3.1416

    print("{0}{0}{0}\n", "=====");
    Frac<int> f {5, 3};
    print("Frac f {{5, 3}}: {}\n", f);
}
