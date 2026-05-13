// ctraits.cpp by Bill Weinman [bw.org]
// as of 2026-05-13

#include <print>
#include <string>
#include <compare>

using std::println;
using std::string;

constexpr char char_lower(const char& c) {
    if (c >= 'A' && c <= 'Z') return c + ('a' - 'A');
    else return c;
}

class ci_traits : public std::char_traits<char> {
public:
    static constexpr bool lt(char_type a, char_type b) noexcept {
        return char_lower(a) < char_lower(b);
    }

    static constexpr bool eq(char_type a, char_type b) noexcept {
        return char_lower(a) == char_lower(b);
    }

    static constexpr int compare(const char_type* s1, const char_type* s2, size_t count) {
        for (size_t i {0}; i < count; ++i) {
            auto diff {char_lower(s1[i]) <=> char_lower(s2[i])};
            if (diff > 0) return 1;
            if (diff < 0) return -1;
            }
        return 0;
    }

    static constexpr const char_type* find(const char_type* p, size_t count, const char_type& ch) {
        const char_type find_c{ char_lower(ch) };
        for (size_t i {0}; i < count; ++i) {
            if (find_c == char_lower(p[i])) return p + i;
        }
        return nullptr;
    }
};

class lc_traits : public std::char_traits<char> {
public:
    static constexpr void assign(char_type& r, const char_type& a) noexcept {
        r = char_lower(a);
    }

    static constexpr char_type* assign(char_type* p, std::size_t count, char_type a) {
        for (size_t i {}; i < count; ++i) p[i] = char_lower(a);
        return p;
    }

    static constexpr char_type* copy(char_type* dest, const char_type* src, size_t count) {
        for (size_t i {0}; i < count; ++i) dest[i] = char_lower(src[i]);
        return dest;
    }

};

using ci_string = std::basic_string<char, ci_traits>;
using lc_string = std::basic_string<char, lc_traits>;

int main() {
    string s {"Foo Bar Baz"};
    ci_string ci_s {"Foo Bar Baz"};

    println("string: {}", s);
    println("ci_string: {}", ci_s);

    ci_string compare1 {"CoMpArE StRiNg"};
    ci_string compare2 {"compare string"};

    if (compare1 == compare2) {
        println("Match! {} == {}", compare1, compare2);
    } else {
        println("no match {} != {}", compare1, compare2);
    }

    size_t found = ci_s.find('b');
    println("found: pos {} char {}", found, ci_s[found]);

    lc_string lc_s {"Foo Bar Baz"};
    println("lc_string: {}", lc_s);

    return 0;
}
