// dir.cpp by Bill Weinman [bw.org]
// as of 2026-05-16

#include <print>
#include <string>
#include <vector>
#include <algorithm>
#include <filesystem>
#include <chrono>

using std::print, std::println, std::format;
using std::string;
using std::vector;
using std::uintmax_t;

namespace fs = std::filesystem;
using de = fs::directory_entry;

struct finfo {
    fs::path p;
    fs::file_status fstat;
    fs::directory_entry dir;
    std::uintmax_t sz;
};

template<>
struct std::formatter<fs::path>: std::formatter<std::string> {
    template<typename FormatContext>
    auto format(const fs::path& p, FormatContext& ctx) const {
        return std::formatter<std::string, char>::format(p.string(), ctx);
    }
};

// return a lowercase version of string s — ascii only
string strlower(string s) {
    auto char_lower = [](char c) -> char {
        if (c >= 'A' && c <= 'Z') return c + ('a' - 'A');
        else return c;
    };
    std::transform(s.begin(), s.end(), s.begin(), char_lower);
    return s;
}

// compare directory_entry objects with strlower
bool dircmp_lc(const de& lhs, const de& rhs) {
    const auto lhstr {lhs.path().string()};
    const auto rhstr {rhs.path().string()};
    return strlower(lhstr) < strlower(rhstr);
}

char type_char(const fs::file_status& st) {
    using fs::file_type;

    switch (st.type()) {
        case file_type::symlink:    return 'l';
        case file_type::directory:  return 'd';
        case file_type::character:  return 'c';
        case file_type::block:      return 'b';
        case file_type::fifo:       return 'p';
        case file_type::socket:     return 's';
        case file_type::regular:    return '-';
        case file_type::unknown:    return 'o';
        default:                    return '?';
    }
}

std::string rwx(fs::perms p) {
    using fs::perms;

    auto bit2char = [](perms p, perms bit, char c) {
        return (p & bit) != perms::none ? c : '-';
    };

    return {
        bit2char(p, perms::owner_read,   'r'),
        bit2char(p, perms::owner_write,  'w'),
        bit2char(p, perms::owner_exec,   'x'),

        bit2char(p, perms::group_read,   'r'),
        bit2char(p, perms::group_write,  'w'),
        bit2char(p, perms::group_exec,   'x'),

        bit2char(p, perms::others_read,  'r'),
        bit2char(p, perms::others_write, 'w'),
        bit2char(p, perms::others_exec,  'x')
    };
}

// std::string time_string(const fs::directory_entry& dir) {
//     using std::chrono::clock_cast;
//     using std::chrono::system_clock;
// 
//     auto tp = clock_cast<system_clock>(dir.last_write_time());
//     return std::format("{:%F %R}", tp);
// }

string size_string(const uintmax_t fsize) {
    constexpr const uintmax_t kilo{ 1024 };
    constexpr const uintmax_t mega{ kilo * kilo };
    constexpr const uintmax_t giga{ mega * kilo };

    if (fsize >= giga ) return format("{}{}", (fsize + giga / 2) / giga, 'G');
    else if (fsize >= mega) return format("{}{}", (fsize + mega / 2) / mega, 'M');
    else if (fsize >= kilo) return format("{}{}", (fsize + kilo / 2) / kilo, 'K');
    else return format("{}B", fsize);
}

void print_dir(const de& dir) {
    using fs::perms;

    const auto fpath {dir.path()};
    const auto fstat {dir.symlink_status()};
    const auto fperm {fstat.permissions()};
    const uintmax_t fsize {is_regular_file(fstat)
      ? file_size(fpath) : 0};
    const auto fn {fpath.filename()};
    const auto permstr {type_char(fstat) + rwx(fperm)};
    // const auto timestr {time_string(dir)};

    string suffix{};
    if (is_symlink(fstat)) {
        suffix = " -> ";
        suffix += fs::read_symlink(fpath).string();
    }
    else if (is_directory(fstat)) suffix = "/";
    else if ((fperm & perms::owner_exec) != perms::none) suffix = "*";

    // println("{} {:>6} {} {}{}", permstr, size_string(fsize), timestr, fn, suffix);
    println("{} {:>6} {}{}", permstr, size_string(fsize), fn, suffix);
}

int main(const int argc, const char** argv) {
    vector<de> entries{};
    fs::path fp {argc > 1 ? argv[1] : "."};

    if (!fs::exists(fp)) {
        const auto cmdname {fs::path{*argv}.filename()};
        println("{}: {} does not exist", cmdname, fp);
        return 1;
    }

    if (is_directory(fp)) {
        for(const auto& de : fs::directory_iterator{fp}) {
            entries.emplace_back(de);
        }
        std::sort(entries.begin(), entries.end(), dircmp_lc);
        for(const auto& e : entries) {
            print_dir(e);
        }
    } else {
        print_dir(de{ fp });
    }

    print("\n");
}
