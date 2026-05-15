// chrono.cpp by Bill Weinman [bw.org]
// as of 2026-05-14

#include <print>
#include <iomanip>
#include <string>
#include <chrono>
#include <ctime>
#include <ratio>

using std::println;
using std::string;
using std::chrono::system_clock;
using std::chrono::steady_clock;
using std::chrono::high_resolution_clock;
using std::chrono::duration;

using seconds = duration<double>;
using milliseconds = duration<double, std::milli>;
using microseconds = duration<double, std::micro>;
using fps24 = duration<unsigned long, std::ratio<1, 24>>;

constexpr uint64_t MAX_PRIME {0x1FFFF};  // largest uint64_t is 0xFFFFFFFFFFFFFFFF

string make_commas(const uint64_t num) {
    auto s = std::to_string(num);
    for (auto i = s.size(); i > 3; i -= 3) {
        s.insert(i - 3, ",");
    }
    return s;
}

seconds timer(uint64_t(*f)()) {
    auto t1 {steady_clock::now()};
    uint64_t count {f()};
    auto t2 {steady_clock::now()};
    seconds secs {t2 - t1};
    println("there are {} primes in range", make_commas(count));
    return secs;
}

uint64_t count_primes() {
    constexpr auto isprime = [](uint64_t n) {
        if (n == 2) return true;
        if (n < 2 || n % 2 == 0) return false;
        for (uint64_t i{3}; i <= n / i; i += 2) {
            if (n % i == 0) return false;
        }
        return true;
    };
    uint64_t count {MAX_PRIME >= 2 ? 1 : 0};  // count 2
    uint64_t start {3};
    uint64_t end {MAX_PRIME};
    
    for (uint64_t i {start}; i <= end; i += 2) {
        if (isprime(i)) ++count;
    }
   return count;
}

int main() {
    auto t = system_clock::now();
    println("system_clock::now is {:%F %T %Z}", t);

    println("counting primes up to {}...", make_commas(MAX_PRIME));
    auto secs {timer(count_primes)};
    println("time elapsed: {:.3f} sec", secs.count());
    println("time elapsed: {:.3f} ms", milliseconds(secs).count());
    println("time elapsed: {:.3e} μs", microseconds(secs).count());
    println("time elapsed: {} frames at 24 fps", floor<fps24>(secs).count());

    println("time elapsed: {:.3}", secs);
    println("time elapsed: {:.3}", milliseconds(secs));
    println("time elapsed: {:.3}", microseconds(secs));
}
