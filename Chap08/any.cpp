// any.cpp by Bill Weinman [bw.org]
// as of 2026-05-14

#include <print>
#include <string>
#include <vector>
#include <list>
#include <any>
#include <typeinfo>

using std::print, std::println;
using std::string;
using std::list;
using std::vector;
using std::any;
using std::any_cast;

using namespace std::literals;

void p_any(const any& a) {
    if (!a.has_value()) {
        println("None.");
    } else if (a.type() == typeid(int)) {
        println("int: {}", any_cast<int>(a));
    } else if (a.type() == typeid(string)) {
        println("string: \"{}\"", any_cast<const string&>(a));
    } else if (a.type() == typeid(list<int>)) {
        print("list<int>: ");
        for (auto& i : any_cast<const list<int>&>(a)) print("{} ", i);
        print("\n");
    } else {
        println("something else: {}", a.type().name());
    }
}

int main() {
    any x {};
    if (x.has_value()) println("have value");
    else println("no value");;

    x = 42;
    if (x.has_value()) {
        println("x has type: {}", x.type().name());
        println("x has value: {}", any_cast<int>(x));
    } else {
        println("no value");;
    }

    x = "abc"s;
    println("x is type {} with value {}", x.type().name(), any_cast<string>(x));

    x = list {1, 2, 3};
    print("x is type {} with value ", x.type().name());
    for (const int& i : any_cast<list<int>&>(x)) print("{} ", i);
    print("\n");

    try {
        println("{}", any_cast<int>(x));
    } catch (std::bad_any_cast& e) {
        println("any: {}", e.what());
    }

    p_any({});
    p_any(47);
    p_any("abc"s);
    p_any(any(list{ 1, 2, 3 }));
    p_any(any(vector{ 1, 2, 3 }));
}
