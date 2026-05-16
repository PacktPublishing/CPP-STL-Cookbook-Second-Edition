// mutex.cpp by Bill Weinman
// as of 2026-05-15

#include <print>
#include <string_view>
#include <thread>
#include <future>
#include <mutex>
#include <list>
#include <optional>

using std::print, std::println;
using std::string_view;
using std::list;
using std::optional;

std::mutex animal_mutex {};

class Animal {
    using friend_t = list<Animal>;
    string_view s_name {"unk"};
    friend_t l_friends {};
public:
    Animal() = delete;
    Animal(const string_view n) : s_name {n} {}

    bool operator==(const Animal& o) const {
        return s_name.data() == o.s_name.data();
    }
    
    bool is_friend(const Animal& o) const {
        for (const auto& a : l_friends) {
            if (a == o) return true;
        }
        return false;
    }

    optional<friend_t::iterator> find_friend(const Animal& o) noexcept {
        for (auto it {l_friends.begin()}; it != l_friends.end(); ++it) {
            if (*it == o) return it;
        }
        return {};
    }
    
    void display() const noexcept {
        std::lock_guard<std::mutex> l(animal_mutex);
        auto n_animals {l_friends.size()};
        print("Animal: {}, friends: ", s_name);
        if (!n_animals) print("none");
        else {
            for (auto n : l_friends) {
                print("{}", n.s_name);
                if (--n_animals) print(", ");
            }
        }
        print("\n");
    }

    bool add_friend(Animal& o) noexcept {
        println("add_friend {} -> {}", s_name, o.s_name);
        if (*this == o) return false;

        std::lock_guard<std::mutex> l(animal_mutex);
        if (!is_friend(o)) {
            l_friends.emplace_back(o);
        }
        if (!o.is_friend(*this)) {
            o.l_friends.emplace_back(*this);
        }

        return true;
    }

    bool delete_friend(Animal& o) noexcept {
        println("delete_friend {} -> {}", s_name, o.s_name);
        if (*this == o) return false;

        std::lock_guard<std::mutex> l(animal_mutex);
        if (auto it = find_friend(o)) {
            l_friends.erase(it.value());
        }
        if (auto it = o.find_friend(*this)) {
            o.l_friends.erase(it.value());
        }

        return true;
    }
};

int main() {
    auto cat1 = std::make_unique<Animal>("Felix");
    auto tiger1 = std::make_unique<Animal>("Hobbes");
    auto dog1 = std::make_unique<Animal>("Astro");
    auto rabbit1 = std::make_unique<Animal>("Bugs");

    auto a1 = std::async([&]{ cat1->add_friend(*tiger1); });
    auto a2 = std::async([&]{ cat1->add_friend(*rabbit1); });
    auto a3 = std::async([&]{ rabbit1->add_friend(*dog1); });
    auto a4 = std::async([&]{ rabbit1->add_friend(*cat1); });

    a1.wait();
    a2.wait();
    a3.wait();
    a4.wait();

    auto p1 = std::async([&]{ cat1->display(); });
    auto p2 = std::async([&]{ tiger1->display(); });
    auto p3 = std::async([&]{ dog1->display(); });
    auto p4 = std::async([&]{ rabbit1->display(); });

    p1.wait();
    p2.wait();
    p3.wait();
    p4.wait();

    auto a5 = std::async([&]{ cat1->delete_friend(*rabbit1); });
    a5.wait();

    auto p5 = std::async([&]{ cat1->display(); });
    auto p6 = std::async([&]{ rabbit1->display(); });
}
