// parallel-algorithms.cpp by Bill Weinman
// as of 2026-05-15

#include <print>
#include <vector>
#include <random>
#include <algorithm>
#include <execution>
#include <chrono>

using std::print, std::println;
using std::chrono::steady_clock;
using std::chrono::duration;

namespace execution = std::execution;

using dur_t = duration<double, std::milli>;

int main() {
    std::vector<unsigned> v(20'000'000);
    std::random_device rng;
    println("generate randoms");
    for (auto &i : v) i = rng() % 0xFFFF'FFFF;

    auto mul2 = [](int n) {return n * 2;};

    auto t0 = steady_clock::now();
    std::transform(v.begin(), v.end(), v.begin(), mul2);
    dur_t dur0 = steady_clock::now() - t0;
    println("no policy: {:.3}ms", dur0.count());
    
    auto t1 = steady_clock::now();
    std::transform(execution::seq, v.begin(), v.end(), v.begin(), mul2);
    dur_t dur1 = steady_clock::now() - t1;
    println("execution::seq: {:.3}ms", dur1.count());
    
    auto t2 = steady_clock::now();
    std::transform(execution::par, v.begin(), v.end(), v.begin(), mul2);
    dur_t dur2 = steady_clock::now() - t2;
    println("execution::par: {:.3}ms", dur2.count());

    auto t3 = steady_clock::now();
    std::transform(execution::par_unseq, v.begin(), v.end(), v.begin(), mul2);
    dur_t dur3 = steady_clock::now() - t3;
    println("execution::par_unseq: {:.3}ms", dur3.count());
}
