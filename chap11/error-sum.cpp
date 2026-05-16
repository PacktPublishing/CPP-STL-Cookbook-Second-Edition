// error-sum.cpp by Bill Weinman [bw.org]
// as of 2026-05-16

#include <print>
#include <cmath>
#include <algorithm>
#include <numeric>
#include <vector>
#include <iterator>
#include <numbers>

using std::print, std::println;
using std::vector;
using std::inner_product;
using std::numbers::pi;

int main() {
    constexpr size_t vlen {100};
    vector<double> ds(vlen);
    vector<int> is(vlen);
    size_t index {};

    // generate sine wave
    auto sin_gen = [&index]{ return 5.0 * sin(index++ * 2 * pi / 100); };
    for (auto& v : ds) v = sin_gen();

    // round to int and copy to is
    index = 0;
    for (auto& v : is) v = static_cast<int>(round(ds.at(index++)));

    // display ds
    for (const auto& v : ds) print("{:-5.2f} ", v);
    print("\n\n");

    // display is
    for (const auto& v : is) print("{:-3d} ", v);
    print("\n\n");

    // error sum
    double errsum = inner_product(ds.begin(), ds.end(), 
        is.begin(), 0.0, std::plus<double>(),
        [](double a, double b){ return pow(a - b, 2); });
    print("error sum: {:.3f}\n\n", errsum);

    // accumulated error
    println("accumulated error:");
    for (auto it {ds.begin()}; it != ds.end(); ++it) {
        double accumsum = inner_product(ds.begin(), it, 
            is.begin(), 0.0, std::plus<double>(),
            [](double a, double b){ return pow(a - b, 2); });
        print("{:-5.2f} ", accumsum);
    }
    print("\n");
}
