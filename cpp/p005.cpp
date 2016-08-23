/*
 * Smallest multiple
 *
 * 2520 is the smallest number that can be divided by each of the numbers
 * from 1 to 10 without any remainder.
 *
 * What is the smallest positive number that is evenly divisible by all of the
 * numbers from 1 to 20?
 */

#include <algorithm>
#include <iostream>
#include <iterator>
#include <numeric>
#include <vector>

// Forward declarations
constexpr long gcd(long a, long b);
constexpr long lcm(long a, long b);

int main(int, char **) {
    /*
     * The smallest number divisible by a set of numbers is their least common
     * multiple (LCM).
     */
    // We could use an arbitrary set of numbers here
    std::vector<long> numbers(20);
    std::iota(numbers.begin(), numbers.end(), 1);

    long result = std::accumulate(numbers.begin(), numbers.end(), 1, &lcm);

    std::cout << "Project Euler - Problem 5: Smallest multiple\n\n";
    std::cout << "The LCM of the numbers\n";
    std::copy(numbers.begin(), numbers.end(),
            std::ostream_iterator<long>(std::cout, " "));
    std::cout << "\nis " << result << '\n';
}

/**
 * Compute the greatest common divisor (GCD) of the specified numbers.
 *
 * @param a A positive number.
 * @param b A positive number.
 * @return The GCD of both numbers.
 */
constexpr long gcd(long a, long b) {
    return b == 0 ? a : gcd(b, a % b);
}

/**
 * Compute the least common multiple (LCM) of the specified numbers.
 *
 * @param a A positive number.
 * @param b A positive number.
 * @return The LCM of both numbers.
 */
constexpr long lcm(long a, long b) {
    return a / gcd(a, b) * b;
}
