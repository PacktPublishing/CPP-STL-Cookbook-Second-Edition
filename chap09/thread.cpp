// thread.cpp by Bill Weinman [bw.org]
// as of 2026-05-15

#include <print>
#include <chrono>
#include <thread>

using std::print, std::println;
using std::thread, std::jthread;

void sleepms(const unsigned ms) {
    using std::chrono::milliseconds;
    std::this_thread::sleep_for(milliseconds(ms));
}

void fthread(const int n) {
    println("This is t{}", n);

    constexpr auto count {5};
    for (size_t i {}; i < count; ++i) {
        sleepms(100 * n);
        println("t{}: {}", n, i + 1);
    }
    println("Finishing t{}", n);
}

int main() {
    thread t1(fthread, 1);
    thread t2(fthread, 2);
    t1.join();
    t2.join();

    println("main() sleep 500 ms");
    sleepms(500);

    jthread t3(fthread, 3);
    jthread t4(fthread, 4);

    println("end of main()");
}
