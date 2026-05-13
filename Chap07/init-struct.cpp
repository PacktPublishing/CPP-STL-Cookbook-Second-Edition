// init-struct.cpp by Bill Weinman [bw.org]
// as of 2026-05-13

#include <print>
#include <iostream>
#include <string>
#include <iomanip>
#include <vector>
#include <fstream>

using std::print, std::println;
using std::cin;
using std::ifstream;
using std::string;
using std::vector;

constexpr const char * fn {"cities.txt"};

struct City {
    string name;
    unsigned long population;
    double latitude;
    double longitude;
};

// skip BOM for UTF-8 on Windows
void skip_bom(auto& fs) {
    const unsigned char boms[] {0xef, 0xbb, 0xbf};
    bool have_bom {true};
    for(const auto& c : boms) {
        if((unsigned char)fs.get() != c) have_bom = false;
    }
    if(!have_bom) fs.seekg(0);
    return;
}

string make_commas(const uint64_t num) {
    auto s = std::to_string(num);
    for (auto i = s.size(); i > 3; i -= 3) {
        s.insert(i - 3, ",");
    }
    return s;
}

std::istream& operator>>(std::istream& in, City& c) {
    in >> std::ws;
    std::getline(in, c.name);
    in >> c.population >> c.latitude >> c.longitude;
    return in;
}

int main() {
    vector<City> cities;
    ifstream infile(fn, std::ios_base::in);
    if(!infile.is_open()) {
        println("failed to open file {}", fn);
        return 1;
    }

    skip_bom(infile);
    for(City c{}; infile >> c;) cities.emplace_back(c);

    println("{} cities imported", cities.size());
    for (const auto& [name, pop, lat, lon] : cities) {
        println("{:.<15} pop {:<10} coords {}, {}", name, make_commas(pop), lat, lon);
    }
}
