/*
 * Summation of primes
 *
 * The sum of the primes below 10 is 2 + 3 + 5 + 7 = 17.
 *
 * Find the sum of all the primes below two million.
 */

#include <iostream>
#include <numeric>
#include <vector>

#include "sieve.hpp"

constexpr Long limit = 2'000'000;

int main(int, char **) {
    auto primes = sieve(limit - 1);
    auto sum = std::accumulate(primes.begin(), primes.end(), Long());

    std::cout << "Project Euler - Problem 10: Summation of primes\n\n";
    std::cout << "The sum of all prime numbers below " << limit << " is\n"
              << sum << '\n';
}
