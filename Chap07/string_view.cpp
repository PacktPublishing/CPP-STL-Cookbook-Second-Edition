// string_view.cpp by Bill Weinman [bw.org]
// as of 2026-05-13

#include <print>
#include <string>
#include <string_view>

using std::print, std::println;
using std::string;
using std::string_view;

int main() {
    char text[]{ "hello" };
    string_view sv1 {text};
    string_view sv2 {sv1};
    string_view sv3 {sv2};
    string_view sv4 {sv3};
    
    string str1 {text};
    string str2 {str1};
    string str3 {str2};
    string str4 {str3};
    
    text[0] = 'J';
    
    println("sv1: {} {}", (void*)sv1.data(), sv1);
    println("sv2: {} {}", (void*)sv2.data(), sv2);
    println("sv3: {} {}", (void*)sv3.data(), sv3);
    println("sv4: {} {}", (void*)sv4.data(), sv4);
    
    println("str1: {} {}", (void*)str1.data(), str1);
    println("str2: {} {}", (void*)str2.data(), str2);
    println("str3: {} {}", (void*)str3.data(), str3);
    println("str4: {} {}", (void*)str4.data(), str4);

    using namespace std::literals;
    auto sv = "hello"sv.substr(1,4);
    println("{}", sv);
    
    auto str_data = sv1.data();
    for (auto i = 0; i < sv1.size(); ++i) {
        print("{} ", str_data[i]);
    }
    print("\n");
}
