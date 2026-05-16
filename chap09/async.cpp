// async.cpp by Bill Weinman [bw.org]
// as of 2026-05-15

#include <print>
#include <string>
#include <list>
#include <chrono>
#include <future>

using std::print, std::println;
using std::string;
using std::list;
using std::chrono::steady_clock;
using std::async;

using launch = std::launch;
using secs = std::chrono::duration<double>;

struct prime_time {
    secs dur {};
    uint64_t count {};
};

prime_time count_primes(const uint64_t max) {
    prime_time ret {};
    constexpr auto isprime = [](uint64_t n) {
        if (n == 2) return true;
        if (n < 2 || n % 2 == 0) return false;
        for (uint64_t i{3}; i <= n / i; i += 2) {
            if (n % i == 0) return false;
        }
        return true;
    };
    ret.count = max >= 2 ? 1 : 0;
    uint64_t start {3};
    uint64_t end {max};
    auto t1 = steady_clock::now();
    for (uint64_t i {start}; i <= end ; ++i) {
        if (isprime(i)) ++ret.count;
    }
    ret.dur = steady_clock::now() - t1;
    return ret;
}

int main() {
    constexpr uint64_t max_prime {0x4FFFFF};  // largest uint64_t is 0xFFFFFFFFFFFFFFFF
    constexpr size_t num_threads {15};
    list<std::future<prime_time>> swarm;

    println("start parallel primes");
    auto t1 {steady_clock::now()};
    for (size_t i {}; i < num_threads; ++i) {
        swarm.emplace_back(async(launch::async, count_primes, max_prime));
    }

    for (auto& f : swarm) {
        static size_t i {};
        auto pt = f.get();
        println("primes({:02}): {} {:.5}", ++i, pt.count, pt.dur);
    }

    secs dur_total {steady_clock::now() - t1};
    println("total duration: {:.5}s", dur_total.count());
}
