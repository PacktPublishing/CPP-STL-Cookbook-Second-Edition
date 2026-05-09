//  todo.cpp by Bill Weinman [bw.org]
//  as of 2026-05-07

#include <print>
#include <string>
#include <map>
#include <ranges>

using std::print, std::println;
using std::string;
using std::multimap;

using todomap = multimap<int, string>;
namespace views = std::views;

void rprint(const todomap& todo) {
    for (auto const& [priority, task] : todo | views::reverse) {
        println("{}: {}", priority, task);
    }
    print("\n");
}

int main() {
    todomap todo {
        {1, "wash dishes"},
        {0, "watch teevee"},
        {2, "do homework"},
        {0, "read comics"}
    };
    rprint(todo);
}
