/*
 * Largest prime factor
 *
 * The prime factors of 13'195 are 5, 7, 13 and 29.
 *
 * What is the largest prime factor of the number 600'851'475'143?
 */

#include <algorithm>
#include <cmath>
#include <cstddef>
#include <iostream>
#include <vector>

#include "sieve.hpp"

constexpr Long number = 600'851'475'143;

int main(int, char **) {
    std::vector<Long> primes;
    // Compute all prime numbers less than or equal to `sqrt(number)`
    do {
        sieve(primes, primes.size() + 100);
    } while(primes.back() < static_cast<Long>(std::sqrt(number)));

    auto it = std::find_if(primes.rbegin(), primes.rend(),
            [](Long x) { return x <= static_cast<Long>(std::sqrt(number)); });
    it = std::find_if(
            it, primes.rend(), [](Long x) { return number % x == 0; });
    auto maxFactor = (it != primes.rend() ? *it : number);

    std::cout << "Project Euler - Problem 3: Largest prime factor\n\n";
    std::cout << "The largets prime factor of " << number << " is\n"
              << maxFactor << '\n';
}
