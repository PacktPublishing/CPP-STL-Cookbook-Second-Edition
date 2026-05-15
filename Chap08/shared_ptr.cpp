// shared_ptr.cpp by Bill Weinman
// as of 2026-05-14

#include <print>
#include <string_view>
#include <memory>

using std::print, std::println;
using std::string_view;
using std::make_shared;
using std::shared_ptr;

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

void check_thing_ptr(const shared_ptr<Thing>& p) {
    if (p) println("{} use count: {}", p->name(), p.use_count());
    else println("invalid pointer");
}

int main() {
    shared_ptr<Thing> p1{ new Thing("Thing 1") };
    auto p2 = make_shared<Thing>("Thing 2");

    {
        println("make 4 copies of p1:");
        auto pa = p1;
        auto pb = p1;
        auto pc = p1;
        auto pd = p1;
        check_thing_ptr(p1);
        pb.reset();
        p1.reset();
        check_thing_ptr(pd);
    }

    check_thing_ptr(p1);
    check_thing_ptr(p2);
    println("end of main()");
}
