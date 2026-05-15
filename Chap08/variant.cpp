// variant.cpp by Bill Weinman [bw.org]
// as of 2026-05-14

#include <print>
#include <variant>
#include <list>
#include <string_view>

using std::print, std::println;
using std::list;
using std::string_view;
using std::visit;

class Animal {
    string_view a_name{};
    string_view a_sound{};
    Animal();
public:
    Animal(string_view n, string_view s) : a_name {n}, a_sound {s} {}
    void speak() const {
        println("{} says {}", a_name, a_sound);
    }
    void sound(string_view s) {
        a_sound = s;
    }
};

class Cat : public Animal {
public:
    Cat(string_view n) : Animal(n, "meow") {}
};

class Dog : public Animal {
public:
    Dog(string_view n) : Animal(n, "arf!") {}
};

class Wookie : public Animal {
public:
    Wookie(string_view n) : Animal(n, "grrraarrgghh!") {}
};

using v_animal = std::variant<Cat, Dog, Wookie>;

struct animal_speaks {
    void operator()(const Dog& d) const {d.speak();}
    void operator()(const Cat& c) const {c.speak();}
    void operator()(const Wookie& w) const {w.speak();}
};

int main() {
    list<v_animal> pets {Cat{"Hobbes"}, Dog{"Fido"}, Cat{"Max"}, Wookie{"Chewie"}};

    println("visit:");
    for (const v_animal& a : pets) {
        visit(animal_speaks{}, a);
    }
    print("\n");

    println("index:");
    for (const v_animal &a : pets) {
        auto idx {a.index()};
        if (idx == 0) get<Cat>(a).speak();
        if (idx == 1) get<Dog>(a).speak();
        if (idx == 2) get<Wookie>(a).speak();
    }
    print("\n");

    println("get_if:");
    for (const v_animal& a : pets) {
        if (const auto c {get_if<Cat>(&a)}; c) {
            c->speak();
        } else if (const auto d {get_if<Dog>(&a)}; d) {
            d->speak();
        } else if (const auto w {get_if<Wookie>(&a)}; w) {
            w->speak();
        }
    }
    print("\n");

    size_t n_cats{}, n_dogs{}, n_wookies{};
    for (const v_animal& a : pets) {
        if(holds_alternative<Cat>(a)) ++n_cats;
        if(holds_alternative<Dog>(a)) ++n_dogs;
        if(holds_alternative<Wookie>(a)) ++n_wookies;
    }
    println("there are {} cat(s), "
               "{} dog(s), "
               "and {} wookie(s)",
               n_cats, n_dogs, n_wookies);
}
