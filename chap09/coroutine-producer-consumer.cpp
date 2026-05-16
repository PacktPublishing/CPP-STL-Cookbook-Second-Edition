// coroutine-producer-consumer.cpp by Bill Weinman [bw.org]
// as of 2026-05-15

#include <print>
#include <coroutine>
#include <deque>
#include <exception>

using std::print, std::println;

constexpr size_t num_items {10};

class task {
public:
    class promise_type;
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
    task(task&& other) noexcept : handle(other.handle) { other.handle = {}; }
    task(const task&) = delete;
    task& operator=(const task&) = delete;
    task& operator=(task&&) = delete;

    ~task() { if (handle) handle.destroy(); }
};

class scheduler {
    std::deque<std::coroutine_handle<>> ready;
    bool f_done {false};
    std::deque<size_t> queue {};
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

    void done(bool f) { f_done = f; }
    bool done() const { return f_done; }
    
    void q_push(const size_t& n) { queue.push_back(n); }
    bool q_empty() const { return queue.empty(); }
    size_t q_pop() {
        size_t n = queue.front();
        queue.pop_front();
        return n;
    }
};

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

// Producer coroutine
task producer(scheduler& sched) {
    for (size_t i = 0; i < num_items; ++i) {
        sched.q_push(i);
        println("produced {}", i);
        co_await yield{sched};
    }
    sched.done(true);
}

// Consumer coroutine
task consumer(scheduler& sched) {
    while (!sched.q_empty() || !sched.done()) {
        if (!sched.q_empty()) {
            println("consumed {}", sched.q_pop());
        }
        co_await yield{sched};
    }
}

int main() {
    scheduler sched{};

    auto p = producer(sched);
    auto c = consumer(sched);

    sched.schedule(p.handle);
    sched.schedule(c.handle);

    sched.run();
}
