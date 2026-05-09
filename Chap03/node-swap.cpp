//  node-swap.cpp by Bill Weinman [bw.org]
//  as of 2026-04-05

#include <print>
#include <map>
#include <string>
// #include <utility>

using std::println;
using std::map;
using std::string;
using std::swap;
using std::move;

using Racermap = map<unsigned int, string>;

void printm(const Racermap &m) {
    println("Rank:");
    for (const auto& [rank, racer] : m) {
        println("{}:{}", rank, racer);
    }
}

template<typename M, typename K>
bool node_swap(M& m, K k1, K k2) {
    if (k1 == k2) return true;
    auto node1 = m.extract(k1);
    auto node2 = m.extract(k2);
    if (node1.empty() || node2.empty()) {
        if (!node1.empty()) m.insert(move(node1));
        if (!node2.empty()) m.insert(move(node2));
        return false;
    }
    swap(node1.key(), node2.key());
    m.insert(move(node1));
    m.insert(move(node2));
    return true;
}

int main() {
    Racermap racers {
        {1, "Mario"}, {2, "Luigi"}, {3, "Bowser"},
        {4, "Peach"}, {5, "Donkey Kong Jr."}
    };
    printm(racers);

    node_swap(racers, 3, 5);
    printm(racers);
}

