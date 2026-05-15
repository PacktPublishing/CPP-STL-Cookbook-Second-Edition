// alias_ptr.cpp by Bill Weinman [bw.org]
// as of 2026-05-14

#include <print>
#include <string>
#include <memory>
#include <tuple>

using std::print, std::println;
using std::string;
using std::make_shared;
using std::shared_ptr;
using std::tuple;

struct Animal {
    string name {};
    string sound {};

    Animal(const string& n, const string& a) : name {n}, sound {a} {
        println("ctor: {}", name);
    }

    ~Animal() {
        println("dtor: {}", name);
    }
};

auto make_animal(const string& n, const string& s) {
    auto ap = make_shared<Animal>(n, s);
    auto np = shared_ptr<string>(ap, &ap->name);
    auto sp = shared_ptr<string>(ap, &ap->sound);
    return tuple(np, sp);
}

int main() {
    auto [name, sound] = make_animal("Velociraptor", "Grrrr!");
    println("The {} says {}", *name, *sound);
    println("Use count: name {}, sound {}", name.use_count(), sound.use_count());
}
