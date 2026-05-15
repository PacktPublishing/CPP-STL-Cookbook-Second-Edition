// unique_ptr.cpp by Bill Weinman
// as of 2026-05-14

#include <print>
#include <string_view>
#include <memory>

using std::print, std::println;
using std::string_view;
using std::make_unique;
using std::unique_ptr;

class Thing {
    string_view thname {"unk"};

public:
    Thing() {
        println("default ctor: {}", thname);
    }

    Thing(const string_view& n) : thname(n) {
        println("param ctor: {}", thname);
    }

    ~Thing() {
        println("dtor: {}", thname);
    }
    
    string_view name() const {
        return thname;
    }
};

void process_thing(const unique_ptr<Thing>& p) {
    if (p) println("processing: {}", p->name());
    else println("invalid pointer");
}

int main() {
    auto p1 = make_unique<Thing>("Thing 1");
    process_thing(p1);
    process_thing(make_unique<Thing>("Thing 2"));

    auto p2 = std::move(p1);
    process_thing(p1);
    process_thing(p2);

    p2.reset(new Thing("Thing 3"));
    process_thing(p2);

    println("end of main()");
}
