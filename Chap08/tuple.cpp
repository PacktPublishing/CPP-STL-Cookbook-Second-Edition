// tuple.cpp by Bill Weinman [bw.org]
// as of 2026-05-14

#include <print>
#include <tuple>
#include <utility>

using std::println, std::print;
using std::tuple;
using std::get;

template<typename... T>
void print_t(const std::tuple<T...>& tup) {
    std::apply([](const auto&... elems) {
        ((std::print("{} ", elems)), ...);
    }, tup);
    std::print("\n");
}

template<typename... T>
constexpr int sum_t(const tuple<T...>& tup) {
    return std::apply([](const auto&... elems) {
        return (elems + ...);
    }, tup);
}

int main() {
    tuple lables {"ID", "Name", "Scale"};
    tuple employee {123456, "John Doe", 3.7};
    tuple nums {1, 7, "forty-two", 47, 73L, -111.11};
    
    print_t(lables);
    print_t(employee);
    print_t(nums);

    tuple ti1 {1, 2, 3, 4, 5};
    tuple ti2 {9, 10, 11, 12, 13, 14, 15};
    tuple ti3 {47, 73, 42};
    auto sum1 {sum_t(ti1)};
    auto sum2 {sum_t(ti2)};
    auto sum3 {sum_t(ti3)};
    println("sum of ti1: {}", sum1);
    println("sum of ti2: {}", sum2);
    println("sum of ti3: {}", sum3);
}
