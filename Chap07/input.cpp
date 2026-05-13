// input.cpp by Bill Weinman [bw.org]
// as of 2026-05-13

#include <print>
#include <iostream>
#include <string>
#include <string_view>
#include <sstream>
#include <cstdio>

using std::print, std::println;
using std::cin;
using std::getchar;
using std::getline;
using std::string;
using std::string_view;
using std::stringstream;

constexpr size_t MAXLINE {1024 * 10};

string trimstr(const string& s) {
    constexpr const char * whitespace{ " \t\r\n\v\f" };

    if (s.empty()) return s;     // empty string
    const auto first{ s.find_first_not_of(whitespace) };
    if (first == string::npos) return {};  // all whitespace
    const auto last{ s.find_last_not_of(whitespace) };
    return s.substr(first, (last - first + 1));
}

void clearistream() {
    int c {};
    cin.clear();
    while (c != '\n' && c != EOF) c = getchar();
}

bool prompt(const string_view s, const string_view s2 = "") {
    if (s2.size()) print("{} ({}): ", s, s2);
    else print("{}: ", s);
    fflush(stdout);
    return true;
}

int main() {
    double a {};
    double b {};
    char s[MAXLINE] {};
    string word {};
    string line {};
    
    const char * p1 {"Words here"};
    const char * p1a {"More words here"};
    const char * p2 {"Please enter two numbers"};
    const char * p3 {"Comma-separated words"};
    
    prompt(p1);
    cin.getline(s, MAXLINE, '\n');
    println("{}", s);
    
    prompt(p1a, "p1a");
    getline(cin, line, '\n');
    println("{}", line);
    
    for (prompt(p2); !(cin >> a >> b); prompt(p2)) {
        println("not numeric");
        clearistream();
    }
    println("You entered {} and {}", a, b);
    clearistream();
    
    line = "";
    prompt(p3);
    while (line.empty()) getline(cin, line);
    stringstream ss(line);
    while (getline(ss, word, ',')) {
        if(word.empty()) continue;
        println("word: [{}]", trimstr(word));
    }
}
