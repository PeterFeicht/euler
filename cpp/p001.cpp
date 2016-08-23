/*
 * Multiples of 3 and 5
 *
 * If we list all the natural numbers below 10 that are multiples of 3 or 5,
 * we get 3, 5, 6 and 9. The sum of these multiples is 23.
 *
 * Find the sum of all the multiples of 3 or 5 below 1000.
 */

#include <iostream>

constexpr int gaussSum(int n);
constexpr int dividableSum(int max, int divider);

constexpr int maxNumber = 1'000;

int main(int, char **) {
    // The sum is just the sum of all multiples of 3 and of 5 added together,
    // minus the multiples of both 3 and 5, which were counted twice.
    auto max = maxNumber - 1;
    auto sum =
            dividableSum(max, 3) + dividableSum(max, 5) - dividableSum(max, 15);

    std::cout << "Project Euler - Problem 1: Multiples of 3 and 5\n\n";
    std::cout << "The sum of all numbers below " << maxNumber
              << " that are multiples of 3 or 5 is\n"
              << sum << '\n';
}

/**
 * Compute the sum of the arithmetic series from 1 to `n`.
 *
 * @param n The maximum number.
 * @return The sum of all numbers from 1 to `n` inclusive.
 */
constexpr int gaussSum(int n) {
    return n * (n + 1) / 2;
}

/**
 * Compute the sum of all numbers evenly divisible by `divider` up to `max`.
 *
 * @param max The maximum number.
 * @param divider The divider.
 * @return The sum of all multiples of `divider` from 1 to `max` inclusive.
 */
constexpr int dividableSum(int max, int divider) {
    return gaussSum(max / divider) * divider;
}
