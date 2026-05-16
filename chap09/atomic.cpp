// atomic.cpp by Bill Weinman [bw.org]
// as of 2026-05-15

#include <print>
#include <string>
#include <thread>
#include <vector>
#include <atomic>

using std::print, std::println;
using std::string;
using std::vector;

std::atomic<bool> ready {};
std::atomic<uint64_t> g_count {};
std::atomic_flag winner {};

constexpr int max_count {1000};
constexpr int max_threads {100};

string make_commas(const uint64_t num) {
    auto s = std::to_string(num);
    for (auto i = s.size(); i > 3; i -= 3) {
        s.insert(i - 3, ",");
    }
    return s;
}

void countem (int id) {
    while (!ready) std::this_thread::yield();
    for (int i {}; i < max_count; ++i) ++g_count;
    if (!winner.test_and_set()) {
        println("thread {:02} won!", id);
    }
};

int main() {
    vector<std::thread> swarm;
    println("spawn {} threads", max_threads);
    for (int i {}; i < max_threads; ++i) {
        swarm.emplace_back(countem, i);
    }
    ready = true;
    for (auto& t : swarm) t.join();
    println("global count: {}", make_commas(g_count));
}
