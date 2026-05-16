// path-ops.cpp by Bill Weinman [bw.org]
// as of 2026-05-16

#include <print>
#include <string>
#include <filesystem>

using std::print, std::println;

namespace fs = std::filesystem;

template<>
struct std::formatter<fs::path>: std::formatter<std::string> {
    template<typename FormatContext>
    auto format(const fs::path& p, FormatContext& ctx) const {
        return std::formatter<std::string, char>::format(p.string(), ctx);
    }
};

int main() {
    constexpr const char* fp{ "testdir/foo.txt" };
    try {
        fs::path p{ fp };
        println("p: {}", p);

        println("current_path: {}", fs::current_path());
        println("absolute(p): {}", fs::absolute(p));
        println("concatenate: {}", fs::path {"testdir"} += "foo.txt");
        println("append: {}", fs::path {"testdir"} /= "foo.txt");
        println("canonical: {}", fs::canonical(fs::path{ "." } /= "testdir"));
        println("equivalent: {}", fs::equivalent("testdir/foo.txt", "testdir/../testdir/foo.txt"));
    } catch (const fs::filesystem_error& e) {
        println("{}", e.what());
        println("path1: {}", e.path1());
        println("path2: {}", e.path2());
    }
}
