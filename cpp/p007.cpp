/*
 * 10'001st prime
 *
 * By listing the first six prime numbers: 2, 3, 5, 7, 11, and 13, we can see
 * that the 6th prime is 13.
 *
 * What is the 10'001st prime number?
 */

#include <iostream>
#include <vector>

#include "sieve.hpp"

constexpr std::size_t index = 10'001;

int main(int, char **) {
    std::vector<Long> primes;
    auto p = sieve(primes, index);

    std::cout << "Project Euler - Problem 7: 10'001st prime\n\n";
    std::cout << "The " << index;
    switch(index % 10) {
        case 1:
            std::cout << (index % 100 != 11 ? "st" : "th");
            break;
        case 2:
            std::cout << (index % 100 != 12 ? "nd" : "th");
            break;
        case 3:
            std::cout << (index % 100 != 13 ? "rd" : "th");
            break;
        default:
            std::cout << "th";
            break;
    }
    std::cout << " prime number is " << p << '\n';
}
