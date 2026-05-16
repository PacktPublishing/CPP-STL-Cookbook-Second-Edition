// call-once.cpp by Bill Weinman [bw.org]
// as of 2026-05-15

#include <print>
#include <thread>
#include <mutex>
#include <list>

using std::print, std::println;
using std::list;
using std::jthread;

constexpr size_t max_threads {25};
std::once_flag init_flag;

void do_init(size_t id) {
    print("do_init ({}): ", id);
}

void do_print(size_t id) {
    std::call_once(init_flag, do_init, id);
    print("{} ", id);
}

int main() {
    list<jthread> spawn;

    for (size_t id{}; id < max_threads; ++id) {
        spawn.emplace_back(do_print, id);
    }
}
