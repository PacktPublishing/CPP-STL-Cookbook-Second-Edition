// formatter.cpp by Bill Weinman [bw.org]
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

int main(const int argc, const char** argv) {
    if (argc != 2) {
        fs::path fn {argv[0]};
        println("usage: {} <path>", fn.filename());
        return 0;
    }

    fs::path dir {argv[1]};
    if (!fs::exists(dir)) {
        println("path: {} does not exist", dir);
        return 1;
    }

    println("path: {}", dir);
    println("filename: {}", dir.filename());
    println("cannonical: {}", fs::canonical(dir));
}
