#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <random>
#include <chrono>
#include "Rng.h"
using namespace std;

int seed = std::chrono::steady_clock::now().time_since_epoch().count();

int rng(int x, int y) {
    static std::mt19937 generator(
        // std::chrono::steady_clock::now().time_since_epoch().count()
        // -1452915051
        seed
    );
    // cerr << "The seed is: " << seed << endl;
    std::uniform_int_distribution<int> distribution(x, y);
    return distribution(generator);
}
