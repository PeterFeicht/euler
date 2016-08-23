/*
 * Longest Collatz sequence
 *
 * The following iterative sequence is defined for the set of positive integers:
 *      n → n/2     (n is even)
 *      n → 3n + 1  (n is odd)
 * Using the rule above and starting with 13, we generate the following
 * sequence:
 *      13 → 40 → 20 → 10 → 5 → 16 → 8 → 4 → 2 → 1
 * It can be seen that this sequence (starting at 13 and finishing at 1)
 * contains 10 terms. Although it has not been proved yet (Collatz Problem),
 * it is thought that all starting numbers finish at 1.
 *
 * Which starting number, under one million, produces the longest chain?
 *
 * NOTE: Once the chain starts the terms are allowed to go above one million.
 */

#include <algorithm>
#include <iostream>
#include <iterator>
#include <stdexcept>
#include <utility>
#include <vector>

// Forward declaration
long countCollatz(long init) throw(std::invalid_argument, std::domain_error);

constexpr long maxNumber = 1'000'000;

int main(int, char **) {
    std::vector<long> maxValues;
    auto maxLength = 0L;

    // Try brute force first, maybe there is a better way
    for(auto j = 1L; j < maxNumber; j++) {
        auto length = countCollatz(j);
        if(length == maxLength) {
            maxValues.push_back(j);
        } else if(length > maxLength) {
            maxValues.clear();
            maxValues.push_back(j);
            maxLength = length;
        }
    }

    std::cout << "Project Euler - Problem 14: Longest Collatz sequence\n\n";
    if(maxValues.size() == 1) {
        std::cout << "The single number below " << maxNumber
                  << " producing a chain of length " << maxLength << " is "
                  << maxValues[0] << '\n';
    } else {
        std::cout << "There are " << maxValues.size() << " numbers below "
                  << maxNumber << " producing a chain of length " << maxLength
                  << ":\n";
        std::copy(maxValues.begin(), maxValues.end(),
                std::ostream_iterator<long>(std::cout, " "));
        std::cout << '\n';
    }
}

/**
 * Count the length of the Collatz sequence for the specified number.
 *
 * @param init The initial value to start the sequence with.
 * @return The number of terms in the sequence, including `init` and 1.
 *
 * @throws std::invalid_argument When `init` is not positive.
 * @throws std::domain_error When an intermediate number overflows.
 */
long countCollatz(long init) throw(std::invalid_argument, std::domain_error) {
    if(init < 1) {
        throw std::invalid_argument("Initial number must be positive.");
    }
    auto next = init;
    auto count = 1L;
    while(next != 1) {
        if(next % 2 == 0) {
            next /= 2;
        } else {
            auto last = std::exchange(next, next * 3 + 1);
            if(next < last) {
                throw std::domain_error("Intermediate number overflowed.");
            }
        }
        count++;
    }
    return count;
}
