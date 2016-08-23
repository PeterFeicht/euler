/*
 * Sum square difference
 *
 * The sum of the squares of the first ten natural numbers is
 *      1^2 + 2^2 + ... + 10^2 = 385 .
 * The square of the sum of the first ten natural numbers is
 *      (1 + 2 + ... + 10)^2 = 55^2 = 3025 .
 * Hence the difference between the sum of the squares of the first ten natural
 * numbers and the square of the sum is 3025 − 385 = 2640.
 *
 * Find the difference between the sum of the squares of the first one hundred
 * natural numbers and the square of the sum.
 */

#include <algorithm>
#include <iostream>
#include <numeric>
#include <vector>

// Forward declaration
constexpr long square(long x);

constexpr long maxNumber = 100;

int main(int, char **) {
    // Sum of the squares
    std::vector<long> numbers(maxNumber);
    std::iota(numbers.begin(), numbers.end(), 1);
    std::transform(numbers.begin(), numbers.end(), numbers.begin(), &square);
    long sumSq = std::accumulate(numbers.begin(), numbers.end(), 0);

    // Square of the sum
    long sqSum = square(maxNumber * (maxNumber + 1) / 2);

    std::cout << "Project Euler - Problem 6: Sum square difference\n\n";
    std::cout << "The difference between the sum of the squares and "
                 "the square of the sum\nof the first "
              << maxNumber << " natural numbers is " << (sqSum - sumSq) << '\n';
}

/**
 * Compute the square of the specified number.
 *
 * @param x A number.
 * @return The square of the number.
 */
constexpr long square(long x) {
    return x * x;
}
