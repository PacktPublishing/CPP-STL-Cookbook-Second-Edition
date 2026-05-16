// sleep.cpp by Bill Weinman [bw.org]
// as of 2026-05-15

#include <print>
#include <chrono>
#include <thread>

using std::print, std::println;
using std::chrono::steady_clock;
using std::chrono::duration;

using namespace std::this_thread;
using namespace std::chrono_literals;

int main() {
    auto t1 = steady_clock::now();
    println("sleep for 1.3 seconds");
    sleep_for(1s + 300ms);

    println("sleep for 2 seconds");
    sleep_until(steady_clock::now() + 2s);

    duration<double> dur1 = steady_clock::now() - t1;
    println("total duration: {:.5}s", dur1.count());
}
