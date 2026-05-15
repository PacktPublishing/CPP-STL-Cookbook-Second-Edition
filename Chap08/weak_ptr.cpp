// weak_ptr.cpp by Bill Weinman [bw.org]
// as of 2026-05-14

#include <print>
#include <string_view>
#include <memory>

using std::print, std::println;
using std::string_view;
using std::make_shared;
using std::shared_ptr;
using std::weak_ptr;

struct circB; // forward declaration

struct circA {
    shared_ptr<circB> p;
    ~circA() { println("dtor A"); }
};

struct circB {
    weak_ptr<circA> p;
    ~circB() { println("dtor B"); }
};

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

void get_weak_thing(const weak_ptr<Thing>& p) {
    if (auto sp = p.lock()) println("{}: count {}", sp->name(), p.use_count());
    else println("no shared object");
}

int main() {
    auto thing1 = make_shared<Thing>("Thing 1");
    weak_ptr<Thing> wp1;
    println("expired: {}", wp1.expired());
    get_weak_thing(wp1);
    print("\n");

    println("assign wp1 = thing1");
    wp1 = thing1;
    get_weak_thing(wp1);
    print("\n");

    println("construct weak_ptr with shared_ptr");
    weak_ptr<Thing> wp2(thing1);
    get_weak_thing(wp2);
    print("\n");

    println("reset thing1");
    thing1.reset();
    get_weak_thing(wp1);
    get_weak_thing(wp2);
    print("\n");

    println("resolve circular reference");
    auto a = make_shared<circA>();
    auto b = make_shared<circB>();

    a->p = b;
    b->p = a;

    println("\nend of main()");
}
