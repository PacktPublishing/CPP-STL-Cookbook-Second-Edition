// producer-consumer.cpp by Bill Weinman
// as of 2026-05-15

#include <print>
#include <deque>
#include <tuple>
#include <condition_variable>
#include <thread>
#include <chrono>

using std::print, std::println;
using std::mutex;
using std::jthread;

using namespace std::chrono_literals;
namespace this_thread = std::this_thread;

using guard_t = std::lock_guard<std::mutex>;
using lock_t = std::unique_lock<std::mutex>;

constexpr size_t num_items {10};
constexpr auto delay_time {200ms};

std::deque<size_t> q {};
std::mutex mtx {};
std::condition_variable cond {};
bool finished {};

void producer() {
    for (size_t i {}; i < num_items; ++i) {
        this_thread::sleep_for(delay_time);
        guard_t x {mtx};
        q.push_back(i);
        cond.notify_all();
    }

    guard_t x {mtx};
    finished = true;
    cond.notify_all();
}

void consumer() {
    while(!finished) {
        lock_t lck {mtx};
        cond.wait(lck, []{
            return !q.empty() || finished;
        });
        while (!q.empty()) {
            println("Got {} from the queue", q.front());
            q.pop_front();
        }
    }
    println("finished!");
}

int main() {
    jthread t1 {producer};
    jthread t2 {consumer};
}
