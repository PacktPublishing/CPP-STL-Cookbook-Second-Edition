//  concatenate.cpp by Bill Weinman [bw.org]
//  as of 2026-05-13

#include <print>
#include <iostream>
#include <string>
#include <sstream>
#include <algorithm>
#include <chrono>

using std::println;
using std::string;
using std::ostringstream;
using std::chrono::high_resolution_clock;
using std::chrono::duration;

void timer(string(*f)()) {
    auto t1 = high_resolution_clock::now();
    string s {f()};
    auto t2 = high_resolution_clock::now();
    duration<double, std::milli> ms = t2 - t1;
    println("{}", s);
    println("duration: {} ms", ms.count());
}

string append_string() {
    println("-> append_string:");
    string a {"a"};
    string b {"b"};
    long n {};
    while (++n) {
        string x {};
        x.append(a);
        x.append(", ");
        x.append(b);
        if(n >= 10000000) return x;
    }
    return "error";
}

string concat_string() {
    println("-> concat_string:");
    string a {"a"};
    string b {"b"};
    long n {};
    while (++n) {
        string x {};
        x += a + ", " + b;
        if(n >= 10000000) return x;
    }
    return "error";
}

string concat_ostringstream() {
    println("-> ostringstream:");
    string a {"a"};
    string b {"b"};
    long n {};
    while (++n) {
        ostringstream x {};
        x << a << ", " << b;
        if(n >= 10000000) return x.str();
    }
    return "error";
}

string concat_format() {
    println("-> append_format:");
    string a {"a"};
    string b {"b"};
    long n {};
    while (++n) {
        string x {};
        x = format("{}, {}", a, b);
        if(n >= 10000000) return x;
    }
    return "error";
}

int main() {
    timer(append_string);
    timer(concat_string);
    timer(concat_ostringstream);
    timer(concat_format);
}
