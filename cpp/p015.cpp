/*
 * Lattice paths
 *
 * Starting in the top left corner of a 2×2 grid, and only being able to move
 * to the right and down, there are exactly 6 routes to the bottom right corner.
 *
 * How many such routes are there through a 20×20 grid?
 */

#include <iostream>

using Long = unsigned long long int;

// Forward declaration
constexpr Long binomial(unsigned n, unsigned k);

constexpr unsigned cols = 20;
constexpr unsigned rows = 20;

int main(int, char **) {
    // The number of paths through an n×m lattice is binomial(n+m, n).
    auto paths = binomial(rows + cols, rows);

    std::cout << "Project Euler - Problem 15: Lattice paths\n\n";
    std::cout << "The number of paths through a " << rows << u8"×" << cols
              << " lattice is\n"
              << paths << '\n';
}

/**
 * Compute the binomial coefficient <i>n</i> over <i>k</i>.
 *
 * @param n Parameter <i>n</i>.
 * @param k Parameter <i>k</i>.
 * @return The binomial coefficient, or 0 if <i>k > n</i>.
 */
constexpr Long binomial(unsigned n, unsigned k) {
    if(k > n) {
        return 0;
    }
    if(k > (n + 1) / 2) {
        return binomial(n, n - k);
    }
    Long result = 1;
    for(unsigned j = 1; j <= k; j++) {
        result = result * (n + 1 - j) / j;
    }
    return result;
}
