//  minimal-coroutine.cpp by Bill Weinman [bw.org]
//  as of 2026-05-15

#include <print>
#include <coroutine>

using std::println;

class say_hello {
public:
    class promise_type; // forward declaration
    using promise_h = std::coroutine_handle<promise_type>;
    promise_h h;

    class promise_type {
    public:
        say_hello get_return_object() {
            return say_hello{
                promise_h::from_promise(*this)
            };
        }
        std::suspend_never initial_suspend() noexcept { return {}; }
        std::suspend_always final_suspend() noexcept { return {}; }
        void return_void() noexcept {}
        void unhandled_exception() {}
    };

    explicit say_hello(promise_h h) : h(h) {}
    say_hello(const say_hello&) = delete;
    say_hello& operator=(const say_hello&) = delete;

    ~say_hello() {
        if (h) h.destroy();
    }
};

say_hello hello() {
    println("before suspension");
    co_await std::suspend_always{};
    println("after resumption");
}

int main() {
    auto d = hello();
    d.h.resume();
}
