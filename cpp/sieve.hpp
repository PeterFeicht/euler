/*
 * Define a function for finding prime numbers.
 */

#include <algorithm>
#include <cstddef>
#include <vector>

using Long = unsigned long long int;

template <typename T>
constexpr T sq(T x) {
    return x * x;
}

/**
 * Fill the specified vector with prime numbers and return the `n`th number.
 * 
 * Note that the vector may be resized, so all iterators may be invalidated.
 *
 * @param primes A vector that will be filled with at least `n` prime numbers.
 *        If the specified vector is not empty, it must already contain the
 *        first `primes.size()` prime numbers, otherwise the result is
 *        undefined.
 * @param n The number of prime numbers to generate (must be positive).
 * @return The `n`th prime number (2 being the 1st prime number).
 */
Long sieve(std::vector<Long> &primes, std::size_t n) {
    static constexpr std::size_t maxSegmentSize = 100'000;

    if(primes.empty()) {
        primes = {2, 3, 5, 7, 11, 13, 17, 19};
    }
    if(primes.size() >= n) {
        return primes[n - 1];
    }

    // Find the next numbers by using a segmented sieve of Eratosthenes
    std::vector<char> mark;
    auto offset = primes.back() + 2;
    while(primes.size() < n) {
        auto segmentSize = std::min<Long>(primes.back(), maxSegmentSize);
        mark.reserve(segmentSize);
        std::fill_n(mark.begin(), segmentSize, 1);
        for(auto it = primes.begin(); sq(*it) < offset + segmentSize; ++it) {
            // Round up to the next multiple of *it >= offset
            auto start = ((offset + *it - 1) / *it) * *it;
            for(auto idx = start - offset; idx < segmentSize; idx += *it) {
                mark[idx] = 0;
            }
        }
        for(std::size_t j = 0; j < segmentSize; j++) {
            if(mark[j]) {
                primes.push_back(offset + j);
            }
        }
        offset += segmentSize + (segmentSize % 2);
    }
    return primes[n - 1];
}
