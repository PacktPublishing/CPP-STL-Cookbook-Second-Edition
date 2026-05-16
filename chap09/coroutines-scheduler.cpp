// coroutines-scheduler.cpp by Bill Weinman [bw.org]
// as of 2026-05-15

#include <print>
#include <coroutine>
#include <deque>
#include <exception>

using std::println;

// Simple coroutine task
class task {
public:
    class promise_type; // forward declaration
    using co_h = std::coroutine_handle<promise_type>;
    co_h handle;

    class promise_type {
    public:
        task get_return_object() {
            return task{
                co_h::from_promise(*this)
            };
        }

        std::suspend_always initial_suspend() noexcept { return {}; }
        std::suspend_always final_suspend() noexcept { return {}; }
        void return_void() noexcept {}
        void unhandled_exception() { std::terminate(); }
    };

    explicit task(co_h h) : handle(h) {}

    // move only, no copying
    task(task&& other) noexcept : handle(other.handle) { other.handle = {}; }
    task(const task&) = delete;
    task& operator=(const task&) = delete;
    task& operator=(task&&) = delete;

    ~task() { if (handle) handle.destroy(); }
};

// Cooperative scheduler
class scheduler {
    std::deque<std::coroutine_handle<>> ready;

public:
    void schedule(std::coroutine_handle<> h) {
        ready.push_back(h);
    }

    void run() {
        while (!ready.empty()) {
            auto h = ready.front();
            ready.pop_front();
            h.resume();
        }
    }
};

// Awaitable used to yield back to the scheduler
class yield {
    scheduler& y_sched;
public:
    explicit yield(scheduler& s) noexcept : y_sched(s) {}
    bool await_ready() const noexcept { return false; }
    void await_resume() const noexcept {}
    
    void await_suspend(std::coroutine_handle<> h) const noexcept {
        y_sched.schedule(h);
    }
};

// Example coroutine tasks
task worker(scheduler& sched, int id) {
    for (int i = 0; i < 3; ++i) {
        println("worker {} step {}", id, i);
        co_await yield {sched};
    }
}

int main() {
    scheduler sched {};

    // Create tasks
    auto t1 = worker(sched, 1);
    auto t2 = worker(sched, 2);
    auto t3 = worker(sched, 3);

    // Schedule initial execution
    sched.schedule(t1.handle);
    sched.schedule(t2.handle);
    sched.schedule(t3.handle);

    // Run event loop
    sched.run();
}
